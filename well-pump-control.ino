#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

#include <ESP8266WiFi.h>
/*

*/
//
//int D0=16; //IO
//int D1=5;  //IO, SCL
//int D2=4;  //IO, SCA
//int D3=0;  //IO, 10k Pull-up
//int D4=2;  //IO, 10k Pull-up, BUILTIN_LED
//int D5=14; //IO, SCK
//int D6=12; //IO, MISO
//int D7=13; //IO, MOSI
//int D8=5;  //IO, 10k Pull-down, SS
// constant for seconds in a minute.
#define MINUTE 60
// Configuration
int setPressure = 45;
int minPressure = 30;
int minPressureDebounceCount = 3;
int maxRunTime = 30*MINUTE;
int pumpCooldownTime = 5*MINUTE;
// Pin Assignments
int relayPin = D5;
int blinkPin = D4;

//state variables
int A0Value = 0;
int measuredPressure = 0;
int lastMeasuredPressure = 0;
int pumpOnTime = 0;
int pumpOnUnderPressureTime = 0;
int minPressureCounter = 0;

//because we use time pump was on for cool down we need to add it to the max run time for comparison.
int  pumpCooldownCheckTime = pumpCooldownTime;
bool relayIsOn = false;
// A0 Reading value at simulated 100 PSI (5v)
int A0at100=939;
// A0 Reading value at simulated 0 PSI (about 0v)
int A0at0=7;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(relayPin, OUTPUT);
  pinMode(blinkPin, OUTPUT);
  pinMode(A0, INPUT);

  Serial.begin(74880);
 
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("                ");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("                ");
}


void readPressure()
{
  
  A0Value = analogRead(A0);
  
  measuredPressure = map(A0Value,A0at0,A0at100,0,100);
  if (lastMeasuredPressure != measuredPressure)
  {
    lastMeasuredPressure = measuredPressure;
    Serial.print("A:");
    Serial.print(A0Value);
    Serial.print(" Pressure:");
    Serial.println(measuredPressure);
    Serial.print(" Last:");
    Serial.println(lastMeasuredPressure);
    lcd.setCursor(0,0);   //Move cursor to character 1 on line 1
    lcd.print("P:    ");
    lcd.setCursor(2,0);   //Move cursor to character 3 on line 1
    lcd.print(measuredPressure);
  }
}

void RelayOn()
{
  if (relayIsOn==false)
  {
    Serial.println("Relay On");
    
  }
  lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
  lcd.print("Pump On         ");
  relayIsOn=true;
  minPressureCounter=0;
  digitalWrite(relayPin, HIGH);   // relay on
}
void RelayOff()
{
  if (relayIsOn)
  {
    Serial.println("Relay Off");

  }
  lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
  lcd.print("Pump Off        ");
  lcd.setCursor(9,0);   //Move cursor to character 1 on line 2
  lcd.print("T-00:00");
  relayIsOn=false;
  digitalWrite(relayPin, LOW);   // relay off
}

void printTime(int line, int startPos, int timeInS)
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
void processPressure()
{
  readPressure();
  if (measuredPressure >= setPressure)
  {
    RelayOff();
    pumpOnTime=0;
    pumpOnUnderPressureTime=0;
    minPressureCounter=0;
  } else if (pumpOnUnderPressureTime >= maxRunTime)
  {
    Serial.println("Max Under Pressure Runtime Exceeded");
    RelayOff();
  } else
  if (measuredPressure < minPressure && pumpOnTime <= 0)
  {
    if (minPressureCounter >=minPressureDebounceCount)
    {
      Serial.println("Turning on Relay");
      pumpOnTime=1;
      pumpOnUnderPressureTime=1;
      minPressureCounter=0;
      RelayOn();
    } else {
      Serial.println("Low Pressure Wait.");
      lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
      lcd.print("Low Press wait. ");
      minPressureCounter++;
    } 
  } 
  else
  {
    if (relayIsOn==false)
    {
      lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
      lcd.print("Pump Off        ");
    }
  }
  if (measuredPressure < setPressure && pumpOnTime > 0)
  {
    if (pumpOnTime==1)
    {
    Serial.print("pumpOnTime: ");
    Serial.println(pumpOnTime);

    } else {
      Serial.print(".");
    }
   
    pumpOnTime++;
    if (measuredPressure < minPressure)
    {
      pumpOnUnderPressureTime++;
    } 
    else
    {
      pumpOnUnderPressureTime=0;
    }
  }
  if (pumpOnTime>0)
  {
    if (relayIsOn==false)
    {
      Serial.print("Cool Down Check ");
      if (pumpCooldownCheckTime >= pumpCooldownTime)
      {
        Serial.println("Reset Pump Run Time");
        pumpOnTime = 0;
        pumpCooldownCheckTime=0;
        pumpOnUnderPressureTime=0;
        minPressureCounter=0;
      } else {
        pumpCooldownCheckTime++;
        Serial.println("Pump Cool Down");
        lcd.setCursor(0,1);   //Move cursor to character 1 on line 2
        lcd.print("Pump Cool   ");
        printTime(1,11,pumpCooldownCheckTime);
      }
    } 
    else
    {
      lcd.setCursor(8,0);   //Move cursor to character 1 on line 2
      lcd.print("RT-00:00");
      printTime(0,11,pumpOnTime);

      pumpCooldownCheckTime=0; 
    }
  }
  
  
  
}
// the loop function runs over and over again forever
void loop() {
  //
  
  
  digitalWrite(blinkPin, HIGH);   // turn the LED on (shows something is running on board)
  processPressure();
  delay(500);                       // wait for a second
  digitalWrite(blinkPin, LOW);    // turn the LED off (shows something is running on board)
  delay(500);                       // wait for a second
  
}
