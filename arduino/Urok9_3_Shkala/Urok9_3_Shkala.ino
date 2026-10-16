/*
  Урок 9. Задание 3 — светодиодная шкала

  Четыре светодиода загораются по очереди, когда крутим ручку.
  У каждого светодиода свой ПОРОГ: он горит, если значение
  с потенциометра больше этого порога.

    значение: 0 … 200 … 400 … 600 … 800 … 1023
    горят:       0     1     2     3     4

  Подключение (у каждого светодиода катод через 220 Ом на GND):
    LED1 зелёный → пин 7      LED3 жёлтый  → пин 5
    LED2 зелёный → пин 6      LED4 красный → пин 4
*/

const int POT  = A0;   // потенциометр
const int LED1 = 7;    // зелёный
const int LED2 = 6;    // зелёный
const int LED3 = 5;    // жёлтый
const int LED4 = 4;    // красный

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT);   // 0…1023
  Serial.println(value);

  // LED1 горит, если значение больше 200
  if (value > 200) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  // LED2 — порог 400
  if (value > 400) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }

  // LED3 — порог 600
  if (value > 600) {
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }

  // LED4 — порог 800
  if (value > 800) {
    digitalWrite(LED4, HIGH);
  } else {
    digitalWrite(LED4, LOW);
  }

  delay(50);   // 20 обновлений в секунду
}
