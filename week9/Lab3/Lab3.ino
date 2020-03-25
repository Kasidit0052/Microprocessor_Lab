#include<SPI.h>
#define DATA_PIN 9
#define CLK_PIN 11
#define SS_PIN 10

int timer1_counter;
int interrupt_count=0;
int mapSeg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void setup()
{
  Serial.begin(9600);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLK_PIN,OUTPUT);
  pinMode(SS_PIN,OUTPUT);
  setLed(0);
  
  noInterrupts();
  TCCR1A = 0;                //RESET TIMER
  TCCR1B = 0;               //RESET TIMER REGISTER
  timer1_counter = 34285;
  TCNT1 = timer1_counter;         //SET TIMER REGISTER VALUE
  
  TCCR1B |= (1 << CS12);          //PRESCALER
  TIMSK1 |= (1 << TOIE1);         //ENABLE TIMER OVERFLOW INTERRUPT
  
  interrupts();
}

void loop()
{
  
}

void setLed(int num)
{
  shiftOut(DATA_PIN,CLK_PIN,MSBFIRST,mapSeg[num]);
  digitalWrite(SS_PIN,HIGH);
  digitalWrite(SS_PIN,LOW);
}

ISR (TIMER1_OVF_vect)
{
  interrupt_count++;
  if(interrupt_count==10){interrupt_count=0;}
  Serial.println(interrupt_count);
  TCNT1 = timer1_counter;
  setLed(interrupt_count);
}
