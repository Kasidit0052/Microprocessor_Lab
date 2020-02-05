//SHCP//
int clk_pin = 13;
//STCP//
int latch_pin = 12;
//DS//
int data_pin = 11;
//Data bit shifting//
int j=0;

//Loop setLED function//
void showNum()
{
  for(int i=0;i<=9;i++)
  {
    if(i==1){setLED(0b00000110);}
    if(i==2){setLED(0b01011011);}
    if(i==3){setLED(0b11001111);}
    if(i==4){setLED(0b01100110);}
    if(i==5){setLED(0b11101101);}
    if(i==6){setLED(0b11111101);}
    if(i==7){setLED(0b00000111);}
    if(i==8){setLED(0b11111111);}
    if(i==9){setLED(0b11101111);}
    if(i==0){setLED(0b10111111);}
    Serial.print("Number: ");
    Serial.print(i);
    Serial.println();
    delay(2000);    
  }
}

//Show LEDs Function//
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
  showNum();
}
