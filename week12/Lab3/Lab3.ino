#define MOTOR_D1_PIN 11
#define MOTOR_D2_PIN 9
#define MOTOR_PWM_PIN 10
#define aCH_PIN 5
#define bCH_PIN 6
#define LED_PIN 7
#define SW1_PIN A0
#define SW2_PIN A1

bool led_status = false;
bool SW1_value,SW2_value;
int timer1_counter;
int mode;

void backward(int speed)
{
  //CW direction
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH);
    analogWrite(MOTOR_PWM_PIN,speed);
}
void forward(int speed)
{
  //CCW direction
    digitalWrite(MOTOR_D1_PIN,HIGH);
    digitalWrite(MOTOR_D2_PIN,LOW);
    analogWrite(MOTOR_PWM_PIN,speed);    
}  

void setSpeed(int speed) 
{ 
  // Motor forward
  if (speed > 0) 
  {
    if (speed > 255) {speed = 255;}
    forward(speed);
  }
  
  // Motor backward
  else if (speed < 0) 
  {  
    speed = speed*(-1);
    if (speed > 255) {speed = 255;}
    backward(speed);
  }
  
  // Motor stop
  else 
  {                   
    forward(1);
  }
}

void InitialInterruptTimer(int start)
{
    noInterrupts();//disable interrupt
    TCCR1A = 0;         //RESET TIMER
    TCCR1B = 0;         //RESER TIMER REGISTER
  
    timer1_counter = start;
    TCNT1 = timer1_counter;   //SET TIMER REGISTER VALUE
  TCCR1B |= (1 << CS12);      //PRESCALER
    TIMSK1 |= (1 << TOIE1);   //ENABLE TIMER OVERFLOW INTERRUPT
  
  interrupts();  //enable interrupt
}


void setup()
{
 Serial.begin(9600);
 pinMode(MOTOR_D1_PIN,OUTPUT);
 pinMode(MOTOR_D2_PIN,OUTPUT);
 pinMode(MOTOR_PWM_PIN,OUTPUT);
 pinMode(aCH_PIN, INPUT_PULLUP);
 pinMode(bCH_PIN, INPUT_PULLUP);
 pinMode(LED_PIN,OUTPUT); 
 pinMode(SW1_PIN, INPUT_PULLUP);
 pinMode(SW2_PIN, INPUT_PULLUP);
 InitialInterruptTimer(34260);  
}

void loop()
{
  SW1_value = digitalRead(SW1_PIN);
  SW2_value = digitalRead(SW2_PIN);
  Serial.println(mode);
  if(SW1_value == false && mode != 1){setSpeed(255);mode = 1;delay(100);}
  if(mode == 1){setSpeed(255);delay(100);}
  if(SW2_value == false && mode != 2){setSpeed(-255);mode = 2;delay(100);}
  if(mode == 2){setSpeed(-255);delay(100);}
}

ISR(TIMER1_OVF_vect)
{
  if(led_status == true){digitalWrite(LED_PIN,LOW);led_status =!led_status;}
  else{digitalWrite(LED_PIN,HIGH);led_status =!led_status;}
  TCNT1 = timer1_counter; 
}
