#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9

int map7seg[10] = {0b10111111,0b00000110,0b01011011,0b11001111,0b01100110,0b11101101,0b11111101,0b00000111,0b11111111,0b11101111};
  
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

void setup()
{
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop()
{
  for(int i=0;i<10;i++)
  {
  spi_write_1(map7seg[i]);
  
  for(int j=0;j<10;j++)
    {
      spi_write_2(map7seg[j]);
      delay(400);
    
    }
  }
}
