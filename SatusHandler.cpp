
#include <inttypes.h>
#include "Arduino.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
#include "StatusHandler.h"

void StatusHandler::setup()
{
    lcd.init();
    lcd.clear();         
    lcd.backlight();      // Make sure backlight is on
    // Print a message on both lines of the LCD.
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("                ");

    lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
    lcd.print("                ");
}

void StatusHandler::updatePressure(int measuredPressure)
{
    static int lastPressure=-1;
    if (lastPressure!=measuredPressure)
    {
      lcd.setCursor(0,0);   //Move cursor to character 1 on line 1
      lcd.print("P:    ");
      lcd.setCursor(2,0);   //Move cursor to character 3 on line 1
      lcd.print(measuredPressure);
      lastPressure=measuredPressure;
    }
}

void StatusHandler::printTime(int line, int startPos, int timeInS)
{
  int min=timeInS/60;
      int sec=timeInS%60;
      lcd.setCursor(startPos,line);   //Move cursor to character 1 on line 2
      if (min<10)
      {
        lcd.print(0);
      }
      lcd.print(min);
      lcd.print(":");
      if (sec<10)
      {
        lcd.print(0);
      }
      lcd.print(sec);
}

void StatusHandler::showMessage(const char* message)
{
    lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
    static char message_str[17];
    sprintf(message_str, "%16s", message);
    lcd.print(message_str);
}