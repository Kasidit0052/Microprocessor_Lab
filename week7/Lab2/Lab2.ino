#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ThreeWire myWire(8,9,10); // IO, SCLK, CERtcDS1302<ThreeWire> Rtc(myWire);
RtcDS1302<ThreeWire> Rtc(myWire);

void printDateTime(const RtcDateTime& dt)
{
  display.setCursor(0,10);
  display.print(dt.Year(), DEC);
  display.print('/');
  display.print(dt.Month(), DEC);
  display.print('/');
  display.print(dt.Day(), DEC);
  display.print(' ');
  display.println();
  display.print(dt.Hour(), DEC);
  display.print(':');
  display.print(dt.Minute(), DEC);
  display.print(':');
  display.print(dt.Second(), DEC);
  display.display();
}
void setup() 
{
  Serial.begin(9600);
  Rtc.Begin();
  RtcDateTime compiled(__DATE__, __TIME__);
  printDateTime(compiled);
  Rtc.SetDateTime(compiled);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
}

void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  display.clearDisplay();
}
