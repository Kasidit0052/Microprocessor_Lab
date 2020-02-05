//SHCP//
int clk_pin = 13;
//STCP//
int latch_pin = 12;
//DS//
int data_pin = 11;
//Data bit shifting//
int j=0;
//Integer Variable Input// 
int integerVariable=7;

//If-Case number switch//
void showNum(int num)
{
  if(num==1){setLED(0b00000110);}
  if(num==2){setLED(0b01011011);}
  if(num==3){setLED(0b11001111);}
  if(num==4){setLED(0b01100110);}
  if(num==5){setLED(0b11101101);}
  if(num==6){setLED(0b11111101);}
  if(num==7){setLED(0b00000111);}
  if(num==8){setLED(0b11111111);}
  if(num==9){setLED(0b11101111);}
  if(num==0){setLED(0b10111111);}
  delay(500);    
}

//Show LEDs function//
void setLED(uint8_t update_dat)
{ 
  digitalWrite(latch_pin,LOW);
  for(int j = 0 ; j < 8 ; j++)
  { 
     digitalWrite(data_pin,update_dat>>(7-j)&0x01);
     digitalWrite(clk_pin,LOW);
     digitalWrite(clk_pin,HIGH);
  }
  digitalWrite(latch_pin,HIGH);
}

void setup() 
{
  //config pin
  Serial.begin(9600);
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
}
void loop()
{
  showNum(integerVariable);
}
