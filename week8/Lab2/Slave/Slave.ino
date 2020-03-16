#define LED_PIN 11
float brightness = 0;
int potValue;
String buff;
void setup() 
{
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    char inByte = Serial.read();
    
    if(('0'<= inByte) && (inByte <= '9'))
    {
      buff += inByte;
    }
    
    if(inByte == '\n')
    {
      potValue = buff.toInt();
      brightness = map(potValue,0,1023,0,255);
      Serial.println(brightness);
      analogWrite(LED_PIN,brightness);
      buff = "";
    }
  }
}
