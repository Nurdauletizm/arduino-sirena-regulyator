/*
  Урок 8. Задание 2, вариант Б — сирена «вой»

  Частота звука плавно растёт, а потом плавно падает:
    звук растёт → горит красный
    звук падает → горит синий
  Плавность получаем циклом for: много маленьких шагов.

  Схема та же, что в задании 1.
*/

const int RED_LED  = 7;    // красный светодиод
const int BLUE_LED = 6;    // синий светодиод
const int BUZZER   = 8;    // пищалка

const int FREQ_LOW  = 600;    // самый низкий звук, Гц
const int FREQ_HIGH = 1500;   // самый высокий звук, Гц
const int STEP      = 10;     // на сколько Гц меняем звук за шаг
const int STEP_TIME = 5;      // длительность одного шага, мс

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Звук растёт — горит красный
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
  for (int freq = FREQ_LOW; freq <= FREQ_HIGH; freq = freq + STEP) {
    tone(BUZZER, freq);   // чуть выше, чем на прошлом шаге
    delay(STEP_TIME);
  }

  // Звук падает — горит синий
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  for (int freq = FREQ_HIGH; freq >= FREQ_LOW; freq = freq - STEP) {
    tone(BUZZER, freq);   // чуть ниже, чем на прошлом шаге
    delay(STEP_TIME);
  }
}
