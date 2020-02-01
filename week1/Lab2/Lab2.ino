int count=0;
void setup() 
{
 DDRD=0xFF;
 DDRB=0x03;
 Serial.begin(9600);
}

void loop() 
{   
  if(((PINB>>2)&0x01)== 0)  
  {
   if(count <=5)
   {
    count++;     
    PORTD=0x02 << count;
    delay(1000);
   }
   else 
   {
    count++;
    PORTD=0x00;
    PORTB=0x01 << count-7;
    delay(1000);
    if(count==9)
    {
      count=1;
      PORTD=0x02 << count;
      delay(1000);
    }
   }
  }
if(((PINB>>3)&0x01)== 0)   
{
  if(count > 7)
  {
    count--;
    PORTD=0x00;
    PORTB=0x01 << count-7;
    delay(1000);    
  }
  else
  {
    count--;
    PORTB=0x00;
    PORTD=0x02 << count;
    delay(1000);
    if(count==0)
    {
      count=8;
      PORTB=0x01 << count-7;
      delay(1000);
    }
  }

}
Serial.println(count);  
}
