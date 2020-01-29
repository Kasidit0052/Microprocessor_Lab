//SHCP
int clk_pin = 13;
//STCP
int latch_pin = 12;
//DS
int data_pin = 11;
// LED shifting
int i=0;
//Data bit shifting
int j=0;

//single LED Blinking
void setLED(uint16_t update_dat)
{ 
  //wait until user unpress the button
  while(((PINC>>1)&0x01)== 0 ||((PINC>>2)&0x01)== 0 ){digitalWrite(clk_pin,LOW);}
  digitalWrite(latch_pin,LOW);
  //bit shifting
  for(int j = 0 ; j < 16 ; j++)
   { 
       digitalWrite(data_pin,update_dat>>(15-j)&0x01);
       digitalWrite(clk_pin,LOW);
       digitalWrite(clk_pin,HIGH);
  }
  digitalWrite(latch_pin,HIGH);
}

void setup() 
{
//config pin
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  setLED(0b0000000000000001);
}
void loop()
{
//Boundary Condition
  if(i==16){i=0; setLED(0b0000000000000001 << i);delay(100);}
  if(i==-1){i=15;setLED(0b0000000000000001 << i);delay(100);}
//Forward Direction
  if(((PINC>>1)&0x01)== 0)
  { 
    i++;
    setLED(0b0000000000000001 << i);
    delay(100);
  }
//Reverse Direction  
  if(((PINC>>2)&0x01)== 0)
  { 
    i--;
    setLED(0b0000000000000001 << i);
    delay(100);
  }
}
