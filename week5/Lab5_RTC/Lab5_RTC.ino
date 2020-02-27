#include<ThreeWire.h>
#include <RtcDS1302.h>
ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
#define LEDPIN 9
int sec,initMin=-1,minute=0,delta;

void printDateTime(const RtcDateTime& dt){
  Serial.print(dt.Year(), DEC);
  Serial.print('/');
  Serial.print(dt.Month(), DEC);
  Serial.print('/');
  Serial.print(dt.Day(), DEC);
  Serial.print(' ');
  Serial.print(dt.Hour(), DEC);
  Serial.print(':');
  Serial.print(dt.Minute(), DEC);
  Serial.print(':');
  Serial.print(dt.Second(), DEC);
  Serial.println();
  Serial.print("Minute Difference");
  Serial.print(':');
  Serial.print(delta, DEC);
  Serial.println();
  sec=dt.Second();
  
  if(initMin==-1)
  {
   initMin=dt.Minute();
  }
  minute=dt.Minute();
  delta=minute-initMin;
  if(delta < 2)
  {
    if(sec % 2 ==0)
    {
    digitalWrite(LEDPIN,HIGH); 
    }
    else
    {
    digitalWrite(LEDPIN,LOW); 
    }
  }
  
  if(delta >= 2)
  {
    digitalWrite(LEDPIN,LOW);
    Serial.print("Stop!");
    Serial.println(); 
  }
  
}
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  Rtc.Begin();
  RtcDateTime setting_time(2020,2,2,0,0,0);
  // year, month, dayOfMonth, hour, minute, second
  // printDateTime(setting_time);
  //Try to comment This line
  Rtc.SetDateTime(setting_time);
  delay(2000);
  Serial.print("EVENTStart:");
  Serial.println();
  
}

void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  delay(400); 
}

//Duration 0.22 seconds 

//Using RTC for couting down time is more effective because
//1.RTC is a clock module which save the time even the arduino is shutting down
//  Power Shortage wouldn't be a problem
//2.RTC is an additional module which might be faster when computing the data
//  and creating an condition instread of Brute-force delay
