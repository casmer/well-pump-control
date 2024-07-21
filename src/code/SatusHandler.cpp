// Copyright (C) 2024 Casey Gregoire <caseyg@lalosoft.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

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
 
void StatusHandler::updateTime(int timeInMs)
{
  _currentTime_ms = timeInMs;
}
void StatusHandler::showMessage(MessageId messageId)
{
  _messageId = messageId;
}

void StatusHandler::updatePressure(int measuredPressure)
{
  _measuredPressure = measuredPressure;
}

void StatusHandler::updatePumpState(bool running)
{
  _pumpRunning = running;
}

void StatusHandler::printPressure()
{
    if (_lastPressure!=_measuredPressure)
    {
      lcd.setCursor(0,0);   //Move cursor to character 1 on line 1
      lcd.print("P:    ");
      lcd.setCursor(2,0);   //Move cursor to character 3 on line 1
      lcd.print(_measuredPressure);
      
      _lastPressure=_measuredPressure;
    }
}

void StatusHandler::printClock()
{
  int currentTime_s = _currentTime_ms/1000;
  if (_lastTime_s != currentTime_s)
  {
    _lastTime_s = currentTime_s;
    //print time starting at character 12 on line 1
    printTime(0,11,currentTime_s);
  }

}

void StatusHandler::printPumpState()
{
  if (_lastPumpRunning!=_pumpRunning)
  {
    _lastPumpRunning=_pumpRunning;
    lcd.setCursor(9,0);   //Move cursor to character 10 on line 1
    lcd.print((_pumpRunning ? "+":"-"));
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


void StatusHandler::printMessage()
{
  if (_lastMessageId != _messageId)
  {
    lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
    switch (_messageId)
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
    _lastMessageId = _messageId;
  }
}

void StatusHandler::printAll()
{
  printPressure();
  printPumpState();
  printClock();
  printMessage();
}