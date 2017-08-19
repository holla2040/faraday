#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "Tensioner.h"

// lcd2004's pcf8574 is set at 0x3F
LiquidCrystal_I2C lcd(0x27, 20, 4);

char outstr[15];
char states[9][7] = {"Idle","Run","Hold","Jog","Alarm","Door","Check","Home","Sleep"};
int state;
uint32_t timeoutState,timeoutTensioner;

Tensioner tensioner(6,7,2,3,4);

void setup() {
  lcd.begin();

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("/ state_   <");
  dtostrf(321,4, 0, outstr);
  lcd.setCursor(14, 0);
  lcd.print(outstr);
  lcd.setCursor(19, 0);
  lcd.print(">");
  lcd.setCursor(0, 1);
  lcd.print("          ooo");
  lcd.setCursor(0, 2);
  lcd.print("message 2");
  lcd.setCursor(0, 3);
  lcd.print("message 3");
  lcd.setCursor(0,3);
  tensioner.begin();

}

char heartbeat[] = "\xDF\xA1"; // see char table in ST076 manual
int i;
double turn;
uint32_t now;
 
void loop() {
  now = millis();
  lcd.setCursor(0, 0);
  lcd.print(heartbeat[(i++)%2]);
  lcd.setCursor(14,1);
  dtostrf(turn,6, 1, outstr);
  lcd.print(outstr);
  turn += 1.1;
  if (turn > 321) turn = 0.0;
  delay(50);
  if (now > timeoutState) {
    lcd.setCursor(2, 0);
    lcd.print("      ");
    lcd.setCursor(2, 0);
    lcd.print(states[(state++)%9]);
    timeoutState = now + 1000;
  }
  tensioner.loop();
  if (now > timeoutTensioner) {
    dtostrf(tensioner.tension,5,1,outstr);
    lcd.setCursor(0, 1);
    lcd.print(outstr);
    timeoutTensioner = now + 250;
  }
}
