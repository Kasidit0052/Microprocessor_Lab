int count=0;
bool mode;
int pot_pin=A0;
int pot_value=0;

void blink_Dled(int count)
{
   PORTD=0x04 <<count;
   delay(pot_value);
}
void blink_Bled(int count)
{
   PORTD=0x00;
   PORTB=0x01 <<count-7;
   delay(pot_value);
}
void setup()
{
    pinMode(pot_pin,INPUT);
    DDRD=0xFF;
    DDRB=0xFF;
    PORTD=0x04;
    delay(pot_value);
}

void loop()
{
  pot_value=analogRead(pot_pin);
  if(((PINC>>1)&0x01)==0){mode=false;}
  if(((PINC>>2)&0x01)==0){mode=true;}
  if(mode==false)
  { 
    if (count<5){PORTB=0x00;count++;blink_Dled(count);}
    else{PORTD=0x00;count++;blink_Bled(count);}
  }
  if(mode==true)
  { 
    if (count>6){PORTD=0x00;count--;blink_Bled(count);}
    else{PORTB=0x00;count--;blink_Dled(count);}
  }
  if(count==8){count=0;PORTD=0x04;delay(pot_value);}
  if(count==-1){count=7;PORTB=0x02;delay(pot_value);}
}
