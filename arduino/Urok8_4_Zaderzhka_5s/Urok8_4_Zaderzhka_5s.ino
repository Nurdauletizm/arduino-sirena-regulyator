/*
  Урок 8. Задание 4 — 5 секунд на выход

  Как у настоящей сигнализации: после нажатия кнопки у
  хозяина есть 5 секунд, чтобы выйти. Всё это время мигает
  ЖЁЛТЫЙ светодиод и тикает пищалка. Потом включается сирена.
  Нажатие кнопки в любой момент — всё выключает.

  У системы три РЕЖИМА (состояния):
    MODE_OFF    — выключено
    MODE_ARMING — постановка на охрану: мигает жёлтый
    MODE_GUARD  — охрана включена: работает сирена

  Подключение (добавился жёлтый светодиод):
    жёлтый светодиод → пин 5 (катод через 220 Ом на GND)
*/

const int RED_LED    = 7;    // красный светодиод
const int BLUE_LED   = 6;    // синий светодиод
const int YELLOW_LED = 5;    // жёлтый светодиод
const int BUZZER     = 8;    // пищалка
const int BUTTON     = 2;    // кнопка

const int HIGH_TONE  = 1000;   // тоны сирены, Гц
const int LOW_TONE   = 750;
const int TICK_TONE  = 2000;   // «тик» во время отсчёта, Гц
const int PHASE_TIME = 400;    // фаза сирены, мс
const int BLINK_TIME = 250;    // жёлтый: 250 мс вкл, 250 мс выкл
const unsigned long ARM_TIME = 5000;   // время на выход: 5 с

// Номера режимов
const int MODE_OFF    = 0;
const int MODE_ARMING = 1;
const int MODE_GUARD  = 2;

int mode = MODE_OFF;            // текущий режим
unsigned long armStart = 0;     // когда начался отсчёт 5 секунд
unsigned long lastSwitch = 0;   // когда последний раз мигнули
bool lightOn = false;           // фаза мигания
int lastButton = HIGH;          // состояние кнопки в прошлый раз

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);   // отпущена = HIGH, нажата = LOW

  Serial.begin(9600);
  Serial.println("Система готова. Нажмите кнопку.");
}

void loop() {
  unsigned long now = millis();

  // ===== 1. КНОПКА: меняем режим =====
  int button = digitalRead(BUTTON);
  if (button != lastButton) {
    delay(50);                        // пережидаем дребезг
    if (button == LOW) {              // нажатие
      if (mode == MODE_OFF) {
        mode = MODE_ARMING;           // начинаем отсчёт
        armStart = now;               // засекаем время
        Serial.println("Постановка на охрану: 5 секунд...");
      } else {
        mode = MODE_OFF;              // из любого режима — выкл
        Serial.println("Охрана выключена");
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        noTone(BUZZER);
        lightOn = false;
      }
    }
    lastButton = button;
  }

  // ===== 2. ПОСТАНОВКА НА ОХРАНУ: мигает жёлтый =====
  if (mode == MODE_ARMING) {
    if (now - lastSwitch >= BLINK_TIME) {   // пора мигнуть
      lastSwitch = now;
      lightOn = !lightOn;
      digitalWrite(YELLOW_LED, lightOn);   // true=HIGH, false=LOW
      if (lightOn) {
        tone(BUZZER, TICK_TONE, 30);  // короткий «тик» со вспышкой
      }
    }
    if (now - armStart >= ARM_TIME) {      // прошло 5 секунд?
      mode = MODE_GUARD;
      digitalWrite(YELLOW_LED, LOW);
      Serial.println("ОХРАНА ВКЛЮЧЕНА!");
    }
  }

  // ===== 3. ОХРАНА: работает сирена =====
  if (mode == MODE_GUARD && now - lastSwitch >= PHASE_TIME) {
    lastSwitch = now;
    lightOn = !lightOn;
    if (lightOn) {
      digitalWrite(RED_LED, HIGH);    // красный + высокий тон
      digitalWrite(BLUE_LED, LOW);
      tone(BUZZER, HIGH_TONE);
    } else {
      digitalWrite(RED_LED, LOW);     // синий + низкий тон
      digitalWrite(BLUE_LED, HIGH);
      tone(BUZZER, LOW_TONE);
    }
  }
}
