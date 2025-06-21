int temp = 0;
int ledList[] = {7, 8, 9, 10, 11};
const int temperaturePin = 0;
float voltage, degreesC, degreesF;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(ledList[i], OUTPUT); 
    digitalWrite(ledList[i], LOW);
  }
}

void loop() {
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;

  Serial.print("\nvoltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);

  int div = degreesC / 16;
  int rem = (int) degreesC % 16;
  if (div == 1) {
    digitalWrite(ledList[4], HIGH);
  } else digitalWrite(ledList[4], LOW);
  div = rem / 8;
  rem %= 8;
  if (div > 0) {
    digitalWrite(ledList[3], HIGH);
  } else digitalWrite(ledList[3], LOW);
  div = rem / 4;
  rem %= 4;
  if (div > 0) {
    digitalWrite(ledList[2], HIGH);
  } else digitalWrite(ledList[2], LOW);
  div = rem / 2;
  rem %= 2;
  if (div > 0) {
    digitalWrite(ledList[1], HIGH);
  } else digitalWrite(ledList[1], LOW);

  if (rem > 0) digitalWrite(ledList[0], HIGH);
  else digitalWrite(ledList[0], LOW);

  delay(5000);
}

float getVoltage(int pin) {
   return (analogRead(pin) * 0.004882814);
}