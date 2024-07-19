#include <inttypes.h>
#include "Arduino.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
#include <StatusHandler.h>

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


constexpr size_t my_str_len(const char* str) {
  return *str ? 1 + my_str_len(str + 1) : 0;
};
#define MESSAGE_HANDLER(messageId, message_str) \
  case messageId: \
      static_assert(my_str_len(message_str) <= 17);  \
      lcd.print(message_str); \
      break;

void StatusHandler::showMessage(MessageId messageId)
{
    lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
    switch (messageId)
    { //                                             ----------------
      MESSAGE_HANDLER(MessageId::NO_MESSAGE,        "                ");
      MESSAGE_HANDLER(MessageId::LOW_PRESSURE_ERROR,"Low Pressure Err");
      MESSAGE_HANDLER(MessageId::PRESSURE_RECOVERY, "Pressure Recover");
      MESSAGE_HANDLER(MessageId::LOW_PRESSURE_WAIT, "      Waiting...");
      MESSAGE_HANDLER(MessageId::PUMP_OFF,          "        Pump Off");
      MESSAGE_HANDLER(MessageId::PUMP_ON,           "         Pump On");
      
    default:
      lcd.print(" INVALID MESSAGE");
      break;
    }

}