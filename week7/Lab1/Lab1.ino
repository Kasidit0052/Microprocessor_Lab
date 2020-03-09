#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define SW_PIN A1
#define SW2_PIN A0

bool buttonStatus=false;
bool button2Status=false;
uint16_t sw1Color;
uint16_t sw2Color;

void setup() 
{
  pinMode(SW_PIN,INPUT_PULLUP);
  pinMode(SW2_PIN,INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() 
{
  if(digitalRead(SW_PIN) == 0)
  {
    buttonStatus=!buttonStatus;
    delay(100);
    if(buttonStatus== true)
    {
     sw1Color=WHITE;delay(100);
    }
    if(buttonStatus== false)
    {
     sw1Color=BLACK;delay(100);
    }
  }
  if(digitalRead(SW2_PIN) == 0)
  {
    button2Status=!button2Status;
    delay(100);
    if(button2Status== true)
    {
     sw2Color=WHITE;delay(100);
    }
    if(button2Status== false)
    {
     sw2Color=BLACK;delay(100);
    }
  }
  
  display.setCursor(0,10);
  display.println("SW1");
  display.drawCircle(70, 16, 10, WHITE);
  display.fillCircle(70, 16, 10, sw1Color);
  display.display();
  
  display.setCursor(0,42);
  display.println("SW2");
  display.drawCircle(70, 48, 10, WHITE);
  display.fillCircle(70, 48, 10, sw2Color);
  display.display();
}
