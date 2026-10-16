/*
  Урок 8. Задание 3 — ПЛОХОЙ вариант (для сравнения!)

  Здесь сирена сделана через delay(), как в задании 2.
  Кнопка проверяется только в начале loop(), а потом
  Arduino «спит» 400 + 400 мс и ничего не замечает.

  Попробуйте быстро нажать кнопку, пока звучит сирена:
  нажатие часто ТЕРЯЕТСЯ. Поэтому в задании 3 мы
  используем millis() вместо delay().
*/

const int RED_LED  = 7;
const int BLUE_LED = 6;
const int BUZZER   = 8;
const int BUTTON   = 2;

const int HIGH_TONE  = 1000;
const int LOW_TONE   = 750;
const int PHASE_TIME = 400;

bool guardOn = false;
int lastButton = HIGH;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Кнопку проверяем ТОЛЬКО здесь — раз в 0,8 секунды!
  int button = digitalRead(BUTTON);
  if (button != lastButton) {
    delay(50);
    if (button == LOW) {
      guardOn = !guardOn;
      if (guardOn) {
        Serial.println("Охрана ВКЛЮЧЕНА");
      } else {
        Serial.println("Охрана выключена");
      }
    }
    lastButton = button;
  }

  if (guardOn) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    tone(BUZZER, HIGH_TONE);
    delay(PHASE_TIME);     // ← 400 мс кнопка НЕ проверяется

    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    tone(BUZZER, LOW_TONE);
    delay(PHASE_TIME);     // ← и ещё 400 мс тоже
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    noTone(BUZZER);
  }
}
