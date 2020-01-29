//SHCP
int clk_pin = 13;
//STCP
int latch_pin = 12;
//DS
int data_pin = 11;
//Potentiometer 
int pot_pin = A0;
int pot_value=0;
//LED shiftBit
int i=0;
// choose LEFT/RIGHTT
int mode;

//single LED  Blinking  Function
void setLED(uint16_t update_dat) 
{
  digitalWrite(latch_pin,LOW);
  for(int i = 0 ; i < 16 ; i++)
  {
     //bit shifting
     digitalWrite(data_pin,update_dat>>(15-i)&0x01);
     digitalWrite(clk_pin,HIGH);
     digitalWrite(clk_pin,LOW);
  }
  //write output
  digitalWrite(latch_pin,HIGH);
}

void setup() 
{
//Config pin
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  pinMode(pot_pin, INPUT);
}

void loop()
{
  //Read potentiometer Value
  pot_value=analogRead(pot_pin);
  //Change switch
  if(((PINC>>1)&0x01)== 0){mode=1;delay(200);}
  if(((PINC>>2)&0x01)== 0){mode=2;delay(200);}
  //Boundary condition
  if(i==16){i=0;setLED(0b0000000000000001 << i);delay(pot_value);}
  if(i==-1){i=15;setLED(0b0000000000000001 << i);delay(pot_value);}
  
  //Forward direction
  if(mode==1)
  {
    i++;
    setLED(0b0000000000000001 << i);
    delay(pot_value);
  }
  
  //Reverse direction
  if(mode==2)
  {
  i--;
    setLED(0b0000000000000001 << i);
    delay(pot_value);   
  }
}
