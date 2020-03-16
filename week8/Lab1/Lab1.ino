#define LED_PIN 11
#define LED2_PIN 10
float brightness = 0;
String buff;
String brightStr;
int    strRange;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    char inByte = Serial.read();
    
    if(inByte == 'L'){buff="";brightStr="";}
    if(('0'<= inByte) && (inByte <= '9'))
    {
      buff += inByte;
    }
    if(inByte == 'B'){buff += inByte;}
    
    if(inByte == 'N')
    {
      
      strRange = buff.length();
      Serial.println(buff);
      Serial.println(strRange);
      
      if(buff[1] == 'B')
      {
        for(int i=2;i<strRange;i++)
        {
          brightStr += buff[i];
        }
      
        brightness = brightStr.toInt();
        Serial.println(brightness);
      }
      
      if(buff[1] != 'B')
      {
          brightness=0.00;
      Serial.println("Pattern Error");
      }
      
      if(buff[0]=='1'){analogWrite(LED_PIN,int(brightness*2.54));}
      if(buff[0]=='2'){analogWrite(LED2_PIN,int(brightness*2.54));}
    }
  }
}
