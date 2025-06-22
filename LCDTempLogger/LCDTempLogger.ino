#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int temp;
const int temperaturePin = 0;
float voltage, degreesC, degreesF;

unsigned short int dailyTemps[96]; //poll every 15 minutes for 24 hrs

void setup() {

  for (int i = 0; i < 96; i++) {
    dailyTemps[i] = 72;
  }


  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello Ryan");
}

void loop() {
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(degreesF);
  lcd.print((char)223);
  lcd.print("F");         

  delay(1000); // Update every second
}

float getVoltage(int pin) {
   return (analogRead(pin) * 0.004882814);
}