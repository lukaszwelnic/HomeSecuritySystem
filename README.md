# Home Secutiry System: Motion-Activated Alarm System with LCD Display

\***_This project was created for teaching purposes and used on workshops for students._**

Project uses a PIR motion sensor, LEDs, a buzzer, a button, and an LCD screen to create a simple security system. The system can be armed or disarmed using a button. When armed, any motion detected will trigger an alarm, displayed on the LCD screen, blink red LED and sound the buzzer.

### Components and Connections
1. Motion Sensor (PIR):

	- VCC → Connect to 5V on the Arduino.
	- OUT (Middle Pin) → Connect to digital pin 8 on the Arduino.
	- GND → Connect to GND on the Arduino.

2. Buzzer:

	- Positive (Long leg) → Connect to digital pin 9 on the Arduino.
	- Negative (Short leg) → Connect to GND on the Arduino.

3. LEDs:

	- Red LED:
		- Anode (Long leg) → Connect to digital pin 10 on the Arduino (via a resistor, typically 220Ω).
	    - Cathode (Short leg) → Connect to GND on the Arduino.
	- Green LED:
	    - Anode (Long leg) → Connect to digital pin 11 on the Arduino (via a resistor, typically 220Ω).
	    - Cathode (Short leg) → Connect to GND on the Arduino.

4. Button:

	- One side of the button → Connect to GND.
	- Other side of the button → Connect to digital pin 12 on the Arduino.
	    - Note: The button pin should be configured as INPUT_PULLUP in the code to utilize the Arduino's internal pull-up resistor. This means the button input reads HIGH when not pressed and LOW when pressed.

5. Potentiometer (for LCD contrast adjustment):

	- Middle Pin → Connect to the V0 pin on the LCD.
	- One Outer Pin → Connect to GND.
	- Other Outer Pin → Connect to 5V (this is not typically necessary, as only the middle pin needs to be connected, but it might be required depending on your potentiometer).

6. LCD (16x2):

    - Pin 1 (VSS) → Connect to GND (Ground).
    - Pin 2 (VDD) → Connect to 5V.
    - Pin 3 (V0) → Connect to the middle pin of the potentiometer (this controls the contrast).
	- Pin 4 (RS) → Connect to digital pin 2 on the Arduino.
	- Pin 5 (RW) → Connect to GND (this sets the LCD to write mode).
    - Pin 6 (E/Enable) → Connect to digital pin 3 on the Arduino.
    - Pin 11 (D4) → Connect to digital pin 4 on the Arduino.
    - Pin 12 (D5) → Connect to digital pin 5 on the Arduino.
    - Pin 13 (D6) → Connect to digital pin 6 on the Arduino.
    - Pin 14 (D7) → Connect to digital pin 7 on the Arduino.
    - Pin 15 (A/LED+) → Connect to 5V (this powers the LCD backlight; use a current-limiting resistor if required).
    - Pin 16 (K/LED-) → Connect to GND (this grounds the LCD backlight).

### Additional Notes:

- Debouncing: The button press is debounced to avoid multiple triggers from a single press. This is implemented using a software debounce mechanism in the code, which ensures stable button state detection.

- LCD Backlight: The LCD backlight (pins 15 and 16) may need a current-limiting resistor, usually around 220Ω, to avoid damaging the backlight LEDs. Check your LCD's datasheet for specific requirements.

- Resistors: It is important to use resistors with the LEDs to prevent excessive current from damaging them. A typical value is 220Ω (I used 330Ω), but this can vary depending on your specific LEDs and desired brightness.

- Power Supply: Ensure your Arduino is powered adequately, especially if driving multiple components (LCD, buzzer, etc.). If the current draw exceeds the Arduino’s capabilities, consider using an external power source.

- Buzzer Frequency: The buzzer is activated with a 1 kHz frequency in the code (tone(buzzerPin, 1000)). You can adjust this frequency if needed, depending on your buzzer's specifications.

- Motion Sensor Sensitivity: Some PIR sensors have adjustable sensitivity and delay via onboard potentiometers. Adjust these if the motion detection is too sensitive or not sensitive enough.
