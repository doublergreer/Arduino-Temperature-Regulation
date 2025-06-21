const int buttonPin = 2;
int buttonState;             
int lastButtonState = LOW;   
int num = 0;
int ledList[] = {7, 8, 9, 10, 11};

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);  

  for (int i = 0; i < 4; i++) {
    pinMode(ledList[i], OUTPUT);
    digitalWrite(ledList[i], LOW);
  }
}

void loop() {
  int div = num / 16;
  int rem = num % 16;
  if (div == 1) {
    digitalWrite(ledList[4], HIGH);
  } else digitalWrite(ledList[4], LOW);
  div = num / 8;
  rem = num % 8;
  if (div == 1) {
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

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        if (num < 32) { 
          num++; 
          Serial.println(num);
        }
        else num = 0;
      }
    }
  }

  lastButtonState = reading;
}
