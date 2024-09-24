#include <Keypad.h>

//Start Keypad setup
const byte ROWS = 4;
const byte COLS = 4;  

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
// End Keypad setup
const int correctLedPin = 13; // Pin for correct code LED. Triggers Green LED and onboard LED for Arduino Uno
const int incorrectLedPin = 11; // Pin for incorrect code LED
const int lockPin = 12; // Pin to trigger the relay/lock
const char correctSequence[] = "1234#"; // Change this code to whatever you want the unlock code to be
char inputSequence[6];
int sequenceIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(correctLedPin, OUTPUT);
  pinMode(incorrectLedPin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH); // Initially lock is engaged
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
    inputSequence[sequenceIndex] = customKey;
    sequenceIndex++;

    if (customKey == '#') {
      inputSequence[sequenceIndex] = '\0'; // Null-terminate the string

      if (strcmp(inputSequence, correctSequence) == 0) {
        Serial.println("correct");
        blinkLED(correctLedPin);
        digitalWrite(lockPin, LOW); // Disengage the lock
      } else {
        Serial.println("incorrect");
        blinkLED(incorrectLedPin);
      }
      sequenceIndex = 0; // Reset for next input
    }
  }
}

void blinkLED(int pin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
  }
}
