#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6
#define aCH_PIN 2
#define bCH_PIN 3
#define POT_PIN A0

#include<SPI.h>
#define Direction_PIN 4
#define CLK_PIN 9
#define SS_PIN 10
#define SS2_PIN 12
#define DATA_PIN 11

volatile int count = 0;
volatile float current_rpm;
volatile float generated_rpm=0;
int encoder_status=0;
bool aCH_value,bCH_value;
int timer1_counter;
String buff;
String setpointStr;

// PID configurations 
volatile int errori = 0,error = 0,pastError=0;
volatile float kp = 0.9;
volatile float ki = 0.1;
volatile float kd = 0.3;
volatile int setpoint =0;
volatile int pid;

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

//Interrupt Function
void InitialInterruptTimer(int input)
{
    noInterrupts();//disable interrupt
    TCCR1A = 0;         //RESET TIMER
    TCCR1B = 0;         //RESER TIMER REGISTER
  
    timer1_counter = input;
    TCNT1 = timer1_counter;   //SET TIMER REGISTER VALUE
  TCCR1B |= (1 << CS12);      //PRESCALER
    TIMSK1 |= (1 << TOIE1);   //ENABLE TIMER OVERFLOW INTERRUPT
  
  interrupts();  //enable interrupt
}

void setup()
{
  pinMode(aCH_PIN, INPUT_PULLUP);
  pinMode(bCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(aCH_PIN),aCH_Callback, RISING);
  attachInterrupt(digitalPinToInterrupt(bCH_PIN),bCH_Callback, RISING);
  InitialInterruptTimer(3035);
  
}

void loop()
{
  while (Serial.available() > 0) 
  {
    char inByte = Serial.read();
    if(inByte == 's'&& buff.length() == 0){buff += inByte;}
    if(inByte == '-'&& buff.length() == 1){buff += inByte;}
    if(('0'<= inByte) && (inByte <= '9')){buff += inByte;}
    if(inByte == 'n')
    {
      if(buff[0] == 's' && buff[1] != '-')
      {
        for(int i=1;i<buff.length();i++)
        {
         if(('0'<= buff[i]) && (buff[i] <= '9')){setpointStr += buff[i];} 
        }
      }
      if(buff[0] == 's' && buff[1] == '-')
      {
        for(int i=1;i<buff.length();i++)
        {
         if(buff[i] == '-' && setpointStr == ""){setpointStr += buff[i];} 
         if(('0'<= buff[i]) && (buff[i] <= '9')){setpointStr += buff[i];}
        }
      }
      int setpoint_tmp = setpointStr.toInt();
      setpoint = map(setpoint_tmp, -100, 100, -255, 255);
      if(setpoint > 255){setpoint = 255;}
      if(setpoint < -255){setpoint = -255;}
      buff = "";
      setpointStr = "";
    }
  }
  setSpeed(generated_rpm);
  Serial.print(generated_rpm);
  Serial.print(",");
  Serial.print(setpoint);
  Serial.println();
}

//CCW direction
void aCH_Callback()
{
  bool bCH_value=digitalRead(bCH_PIN);
  if(bCH_value==false)
  {
    encoder_status=1;
    count--;
  }
} 

//CW direction
void bCH_Callback()
{
  bool aCH_value=digitalRead(aCH_PIN);
  if(aCH_value==false)
  {
    encoder_status=2;
    count++;
  }
}

ISR(TIMER1_OVF_vect)
{
  current_rpm =(float(float(count)/230)/float(1.0/60));              
  error = setpoint - current_rpm;
  errori+=error;
  pid = kp*(float)(error) + ki*(float)(errori)+kd*(error-pastError);
  generated_rpm += pid*0.9;
  if(generated_rpm > 255)
  {
    generated_rpm = 255;
  }
    if(generated_rpm < -255)
  {
    generated_rpm = -255;
  }
  count = 0; 
  pastError = error;
  TCNT1 = timer1_counter;
}
