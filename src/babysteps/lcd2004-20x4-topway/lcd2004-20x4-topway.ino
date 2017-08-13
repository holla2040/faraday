#include <Wire.h>
#include "LiquidCrystal_I2C.h"

// lcd2004's pcf8574 is set at 0x3F
LiquidCrystal_I2C lcd(0x27, 20, 4);

uint32_t timeout;
void setup()
{
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("Hello, world!");
}

void loop()
{
  uint32_t t = millis();
  double v = sin(t / 100000.0);
  if (millis() > timeout) {
    lcd.setCursor(0, 0);
    lcd.print(10 * v, 4);
    lcd.print("  ");
    lcd.setCursor(2, 2);
    lcd.print(100 * v, 4);
    lcd.print("  ");
    lcd.setCursor(10, 0);
    lcd.print(1000 * v, 4);
    lcd.print("  ");

    timeout = t + 250;
    lcd.setCursor(10, 3);
    lcd.print(millis() - t);
  }
}
