#include <LiquidCrystal.h>

// Initialize the LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int pirPin = 8;
const int buzzerPin = 9;
const int redLEDPin = 10;
const int greenLEDPin = 11;
const int toggleButtonPin = 12;

bool isArmed = false;
bool lastButtonState = HIGH;  // Last button state (initially unpressed)
bool buttonPressed = false;   // To debounce the button press
bool motionDetected = false;  // To track motion detection
bool dangerDisplayed = false; // To track if "DANGER!" is displayed

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // debounce time in milliseconds
unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 250; // interval at which to blink (milliseconds)

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(toggleButtonPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("System Disarmed");
  digitalWrite(greenLEDPin, HIGH); // Green LED on by default
}

void loop() {
  // Read the button state
  bool currentButtonState = digitalRead(toggleButtonPin);

  // Check if the button is pressed (active LOW)
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState == LOW && !buttonPressed) {
      buttonPressed = true;
      isArmed = !isArmed; // Toggle the armed state
      
      if (isArmed) {
        lcd.clear();
        lcd.print("System Armed");
        digitalWrite(greenLEDPin, LOW);
        motionDetected = false; // Reset motion detected state
        dangerDisplayed = false; // Reset danger display flag
      } else {
        lcd.clear();
        lcd.print("System Disarmed");
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, HIGH);
        noTone(buzzerPin); // Turn off the buzzer if it was on
        dangerDisplayed = false; // Reset danger display flag
      }
    }
  }

  // Update the last button state
  lastButtonState = currentButtonState;

  // Reset the buttonPressed flag after the button is released
  if (currentButtonState == HIGH) {
    buttonPressed = false;
  }

  // If the system is armed, check for motion detection
  if (isArmed) {
    int motion = digitalRead(pirPin);
    if (motion == HIGH && !motionDetected) {
      motionDetected = true; // Set motion detected flag
    }

    // If motion is detected, display danger message and blink the red LED
    if (motionDetected) {
      if (!dangerDisplayed) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("DANGER!");
        lcd.setCursor(0, 1);
        lcd.print("Motion detected!");
        dangerDisplayed = true; // Set the flag to indicate the danger message is displayed
        tone(buzzerPin, 1000);  // Activate buzzer
      }

      unsigned long currentTime = millis();
      if (currentTime - lastBlinkTime >= blinkInterval) {
        lastBlinkTime = currentTime;
        int ledState = digitalRead(redLEDPin);
        digitalWrite(redLEDPin, !ledState); // Toggle LED state
      }
    }
  } else {
    noTone(buzzerPin); // Turn off the buzzer if the system is disarmed
    digitalWrite(redLEDPin, LOW); // Ensure red LED is off when disarmed
  }
}