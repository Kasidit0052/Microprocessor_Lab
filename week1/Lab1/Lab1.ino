void setup() 
{
DDRD=0xFF;
DDRB=0x03;
}

void loop() 
{ 
  for(int i=0;i<=8;i++)
    { 
      if(i<=5)
      {
      PORTD=0x04 << i; 
      delay(1000);
      }
      if(i==5)
      {
        PORTD=0x00;
        PORTB=0x00;
      }
      if(i>5)           
      {
      PORTB=0x01 << i-6;
      delay(1000);
      }
    }
  PORTD=0x00;
  PORTB=0x00;
}    
