/*
  Урок 8. Задание 3 — кнопка режима «Охрана»

  Нажали кнопку  → режим «Охрана» включён, работает сирена.
  Нажали ещё раз → режим выключен, тишина.

  Главное: в сирене больше НЕТ delay()! Вместо того чтобы
  «спать», Arduino постоянно смотрит на часы millis() и
  поэтому успевает проверять кнопку тысячи раз в секунду.

  Подключение (добавилась кнопка):
    кнопка: одна ножка → пин 2, другая → GND.
    Резистор для кнопки не нужен — включим встроенный
    подтягивающий резистор командой INPUT_PULLUP.
*/

const int RED_LED  = 7;    // красный светодиод
const int BLUE_LED = 6;    // синий светодиод
const int BUZZER   = 8;    // пищалка
const int BUTTON   = 2;    // кнопка

const int HIGH_TONE  = 1000;   // высокий тон, Гц
const int LOW_TONE   = 750;    // низкий тон, Гц
const int PHASE_TIME = 400;    // длительность фазы сирены, мс

bool guardOn = false;           // режим «Охрана»: true — включён
bool redPhase = false;          // фаза сирены: true — красная
unsigned long lastSwitch = 0;   // когда последний раз меняли фазу
int lastButton = HIGH;          // состояние кнопки в прошлый раз

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);   // отпущена = HIGH, нажата = LOW

  Serial.begin(9600);
  Serial.println("Система готова. Нажмите кнопку.");
}

void loop() {
  unsigned long now = millis();   // мс с момента включения

  // ===== 1. КНОПКА =====
  int button = digitalRead(BUTTON);
  if (button != lastButton) {       // кнопку нажали или отпустили
    delay(50);                      // пережидаем дребезг контактов
    if (button == LOW) {            // это было НАЖАТИЕ
      guardOn = !guardOn;           // переключаем: вкл ↔ выкл
      if (guardOn) {
        Serial.println("Охрана ВКЛЮЧЕНА");
      } else {
        Serial.println("Охрана выключена");
        digitalWrite(RED_LED, LOW);   // гасим свет
        digitalWrite(BLUE_LED, LOW);
        noTone(BUZZER);               // и выключаем звук
      }
    }
    lastButton = button;            // запоминаем состояние
  }

  // ===== 2. СИРЕНА (только в режиме «Охрана») =====
  if (guardOn && now - lastSwitch >= PHASE_TIME) {  // пора?
    lastSwitch = now;               // запоминаем время смены
    redPhase = !redPhase;           // красная ↔ синяя
    if (redPhase) {
      digitalWrite(RED_LED, HIGH);  // красный + высокий тон
      digitalWrite(BLUE_LED, LOW);
      tone(BUZZER, HIGH_TONE);
    } else {
      digitalWrite(RED_LED, LOW);   // синий + низкий тон
      digitalWrite(BLUE_LED, HIGH);
      tone(BUZZER, LOW_TONE);
    }
  }
}
