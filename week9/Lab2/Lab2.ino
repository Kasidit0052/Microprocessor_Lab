#define LED_PIN 8
#define SW_PIN 2
bool buttonStatus=true;
int mode=1,tmp;
int timer1_counter;
int interrupt_count=0;
bool toggle=true;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_PIN),ISR_Callback, RISING);
  
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

void ISR_Callback()
{
  mode++;
  if(mode>3){mode=1;}
  interrupt_count=0;
} 

ISR (TIMER1_OVF_vect)
{
  interrupt_count++;
  Serial.println(interrupt_count);
  TCNT1 = timer1_counter;
  if(interrupt_count==mode)
  {
    interrupt_count=0;
    digitalWrite(LED_PIN, toggle);
    toggle=!toggle;
  }
}
