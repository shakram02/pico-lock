/**
   A Serial-based locking system using Arduino.

   A password is entered into the serial monitor and is checked with
   the password stored on the Arduino and adjust the portentiometer
   to a correct value.

   The potentometer value is shown on the LCD to make it easier
   to lookup the desired value.

   Assume that the password is 5 digits.

   Components
   - LCD Circuit (circuit as on website)
        LCD RS pin to digital pin 12
        LCD Enable pin to digital pin 11
        LCD D4 pin to digital pin 5
        LCD D5 pin to digital pin 4
        LCD D6 pin to digital pin 3
        LCD D7 pin to digital pin 2
        LCD R/W pin to ground
        LCD VSS pin to ground
        LCD VCC pin to 5V
        10K resistor:
        ends to +5V and ground
        wiper to LCD VO pin (pin 3)

   If anythihng isn't clear please refer to:
   https://www.arduino.cc/en/Reference/ParseInt
   https://www.arduino.cc/en/Tutorial/ReadASCIIString
   https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
*/
#include <LiquidCrystal.h>

const int PASSWORD = 53;
const int LED_PIN = 13;
const int LCD_BLINK_DELAY_MS = 500;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // TODO read potentiometer
  // TODO display potentiometer value
  // TODO output on a green LED if all is well, maybe a red LED otherwise
  if (checkNumericPassword()) {
    Serial.println("Acces!");
    // Do other stuff

    // Blink text then delete it.
    blinkText(3);
    lcd.clear();
  }
}

boolean checkNumericPassword() {
  // To get a consistent result, use No Line Ending in Serial monitor
  // the line ending is parsed using parseInt, and since it's an invalid
  // input, 0 will be returned or just flush the serial after each parse

  // Notify about returning false, otherwise the last returned value will be
  // re-returned, which is a really bad bug. It happens *probably* because the address of the
  // return value isn't changed, nor the value within that address
  if (!Serial.available()) return false;

  long inputPassword = Serial.parseInt();
  Serial.flush();

  return inputPassword == PASSWORD;
}



/**
   Blinks the text on the LCD for a given number of times
*/
void blinkText(int times) {
  for (int i = 0; i < times; i++) {
    lcd.noDisplay();
    delay(LCD_BLINK_DELAY_MS);
    lcd.display();
    delay(LCD_BLINK_DELAY_MS);
  }
}
