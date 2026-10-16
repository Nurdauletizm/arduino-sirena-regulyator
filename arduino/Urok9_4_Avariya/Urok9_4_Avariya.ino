/*
  Урок 9. Задание 4 — аварийный сигнал

  Шкала работает как в задании 3. Если повернуть ручку почти
  до упора (значение больше 1000), включается АВАРИЙНЫЙ
  сигнал: пищалка часто и прерывисто пищит.

  Подключение (добавилась пищалка):
    пищалка «+» → пин 8, пищалка «−» → GND
*/

const int POT    = A0;   // потенциометр
const int LED1   = 7;    // зелёный
const int LED2   = 6;    // зелёный
const int LED3   = 5;    // жёлтый
const int LED4   = 4;    // красный
const int BUZZER = 8;    // пищалка

const int ALARM_LEVEL = 1000;   // порог аварии (максимум 1023)
const int ALARM_TONE  = 2500;   // частота аварийного писка, Гц

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT);   // 0…1023

  // ----- Шкала (как в задании 3) -----
  if (value > 200) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }
  if (value > 400) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }
  if (value > 600) {
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }
  if (value > 800) {
    digitalWrite(LED4, HIGH);
  } else {
    digitalWrite(LED4, LOW);
  }

  // ----- Авария: ручка почти на максимуме -----
  if (value > ALARM_LEVEL) {
    Serial.print("АВАРИЯ! Значение: ");
    Serial.println(value);
    tone(BUZZER, ALARM_TONE);   // писк…
    delay(100);
    noTone(BUZZER);             // …пауза
    delay(100);
  } else {
    noTone(BUZZER);             // всё в норме — тишина
    delay(50);
  }
}
