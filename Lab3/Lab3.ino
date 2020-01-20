int duration=500;
void setup() 
{
 Serial.begin(9600);
 DDRD=0xFF;
 DDRB=0x03;
}

void loop() 
{ 
for(int i=0;i<=8;i++)
    { 
      if(i<=5)
      {     
        if(((PINB>>3)&0x01)== 0){duration += 10;}
        if(((PINB>>2)&0x01)== 0){duration -= 10;}
        if(duration==0){duration =100;}
      Serial.println(duration);  
      PORTD=0x04 << i; 
      delay(duration);
      }
      
      if(i==5)
      {
        PORTD=0x00;
        PORTB=0x00;
      }
      
      if(i>5)          
      {
        if(((PINB>>3)&0x01)== 0){duration += 10;}
        if(((PINB>>2)&0x01)== 0){duration -= 10;}
        if(duration==0){duration =100;}
      Serial.println(duration);    
      PORTB=0x01 << i-6;
      delay(duration);
      }
    }
  PORTD=0x00;
  PORTB=0x00;
}    
