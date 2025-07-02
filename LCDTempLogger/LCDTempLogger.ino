#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// custom bitmap up/down arrows
byte arrowUp[8] = {
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};

byte arrowDown[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};

const int temperaturePin = 0;
float voltage, degreesC, degreesF;

unsigned long lastSwitch = 0, lastLogPoll = 0;
int slideIndex = 0;
const String clearRow = "                ";

int temp, pollCount = 0;
unsigned short int dailyTemps[96]; //poll every 15 minutes for 24 hrs
float avg;

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, arrowUp);
  lcd.createChar(1, arrowDown);

  lcd.setCursor(0, 0);
  lcd.print("Good Evening,RRG");
}

void loop() {
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0 / 5.0) + 32.0;

  // Refresh every 5 seconds
  if (millis() - lastSwitch >= 5000) {
    lastSwitch = millis();

    lcd.setCursor(0, 1);
    lcd.print(clearRow);

    lcd.setCursor(0, 1);
    if (slideIndex == 0) {
      lcd.print("Temp: ");
      lcd.print(degreesF, 1);
      lcd.print((char)223);
      lcd.print("F");
      slideIndex++;
    } else if (slideIndex == 1) {
      lcd.print("24H Avg: ");
      if (pollCount > 0) {
        lcd.print(avg, 1);
        lcd.print((char)223);
        lcd.print("F");
        lcd.write(degreesF >= avg ? (uint8_t)0 : (uint8_t)1);
      } else {
        lcd.print("N/A");
      }
      slideIndex++;
    } else if (slideIndex == 2) {
      lcd.print("Uptime: ");
      slideIndex++;
      displayUpTime();
    } else {
      lcd.print("Poll Count: ");
      lcd.print(pollCount);
      slideIndex = 0;
    }
  }
  //log every 15 mins
  if (millis() - lastLogPoll >= 900000) {
    if (pollCount > 95) pollCount = 0; //reset after 24 hrs
    dailyTemps[pollCount] = (int) degreesF * 10; //typecast w/ 1 decimal precision
    pollCount++;
    lastLogPoll = millis();
    avg = calculateAvg();
  }
}

float getVoltage(int pin) {
   return (analogRead(pin) * 0.004882814);
}

void displayUpTime() {
  for (int i = 0; i < 5; i++) {  
    lcd.setCursor(8, 1); 
    unsigned long seconds = millis() / 1000;

    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    if (hours < 10) lcd.print('0');
    lcd.print(hours);
    lcd.print(':');

    if (minutes < 10) lcd.print('0');
    lcd.print(minutes);
    lcd.print(':');

    if (secs < 10) lcd.print('0');
    lcd.print(secs);

    delay(1000);
  }
}

float calculateAvg() {
  float sum = 0;
  for (int i = 0; i < pollCount; i++) {
    sum += dailyTemps[i] / 10;   
  }

  return sum / pollCount;
}