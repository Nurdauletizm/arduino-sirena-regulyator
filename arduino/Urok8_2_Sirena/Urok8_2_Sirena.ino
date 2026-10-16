/*
  Урок 8. Задание 2 — «Сирена»

  Синхронизируем звук со светом. Каждая фаза сирены — это
  свет И звук, которые меняются в один и тот же момент:
    горит КРАСНЫЙ → звучит ВЫСОКИЙ тон
    горит СИНИЙ   → звучит НИЗКИЙ тон

  Схема та же, что в задании 1.
*/

const int RED_LED  = 7;    // красный светодиод
const int BLUE_LED = 6;    // синий светодиод
const int BUZZER   = 8;    // пищалка

const int HIGH_TONE  = 1000;   // высокий тон, Гц
const int LOW_TONE   = 750;    // низкий тон, Гц
const int PHASE_TIME = 400;    // длительность одной фазы, мс

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Фаза 1: красный + высокий тон
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
  tone(BUZZER, HIGH_TONE);   // звук меняем сразу вместе со светом
  delay(PHASE_TIME);         // держим фазу 0,4 секунды

  // Фаза 2: синий + низкий тон
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  tone(BUZZER, LOW_TONE);
  delay(PHASE_TIME);
}
