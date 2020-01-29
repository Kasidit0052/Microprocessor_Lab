//SHCP
int clk_pin = 13;
//STCP
int latch_pin = 12;
//DS
int data_pin = 11;

//Single LED blinking
void setLED(uint16_t update_dat) 
{
 digitalWrite(latch_pin,LOW);
 for(int i = 0 ; i < 16 ; i++)
 {
    digitalWrite(data_pin,update_dat>>(15-i)&0x01);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
 }
 digitalWrite(latch_pin,HIGH);
}

void setup() 
{
// Config pin
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
}
void loop()
{
//LED blinking loop
 for(int i=0;i<16;i++)
 {
   setLED(0b0000000000000001 << i);
   delay(100);
 }
}
