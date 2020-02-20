#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define BUZZER_PIN 12

int count=0;
int map7seg[10] = {0b10111111,0b00000110,0b01011011,0b11001111,0b01100110,0b11101101,0b11111101,0b00000111,0b11111111,0b11101111};
bool iscount=false;
int one,ten;

void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
  
}

void spi_write_2(unsigned char cData)
{
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
  
}

void showLed()
{
    one = (count % 10);
    ten = (count/10)%10;  
    spi_write_1(map7seg[ten]);
    spi_write_2(map7seg[one]);
    delay(100);
}

void countDown()
{
  if(iscount == true)
  {
    count--;
    showLed();
    if(count <0)
    {spi_write_1(map7seg[0]);
     spi_write_2(map7seg[0]);
     tone(BUZZER_PIN, 1000); // Send 1KHz sound signal...
     delay(1000);            // ...for 1 sec
     noTone(BUZZER_PIN);         // Stop sound...
     delay(1000);            // ...for 1sec
     iscount = !iscount;
    }
    delay(100);
  }
  
}

void setup()
{
  Serial.begin(9600);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  spi_write_1(map7seg[0]);
  delay(100);
  spi_write_2(map7seg[0]);
}

void loop()
{ 
  if((PINC & 0x01)==0)
  {
    count++;
    showLed();
    if(count == 100){count=0;showLed();}
  }
  
  if(((PINC >> 1) & 0x01)==0)
  {
    count--;
    showLed();
    if(count == -1){count=99;showLed();}
  }
  if(((PINC >> 2) & 0x01)==0)
  {
  iscount = !iscount;
    delay(500);
  }
  countDown();
}
