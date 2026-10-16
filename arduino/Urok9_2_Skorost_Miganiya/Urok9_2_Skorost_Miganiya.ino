/*
  Урок 9. Задание 2 — скорость мигания от ручки

  Чем дальше повернули ручку, тем ДЛИННЕЕ пауза delay()
  и тем медленнее мигает светодиод.
  Функция map() пересчитывает число 0…1023 в паузу 50…1000 мс.

  Подключение (добавился светодиод):
    светодиод → пин 7 (катод через 220 Ом на GND)
*/

const int POT = A0;   // потенциометр
const int LED = 7;    // светодиод

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT);                 // 0…1023
  int pause = map(value, 0, 1023, 50, 1000);   // 50…1000 мс

  Serial.print("Значение: ");
  Serial.print(value);
  Serial.print("   Пауза: ");
  Serial.print(pause);
  Serial.println(" мс");

  digitalWrite(LED, HIGH);   // включили
  delay(pause);              // ждём
  digitalWrite(LED, LOW);    // выключили
  delay(pause);              // снова ждём
}
