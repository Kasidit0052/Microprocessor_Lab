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

int map7Seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int count = 0,encoder_status=0;
bool aCH_value,bCH_value;

// PID configurations 
int errori = 0,error = 0;
float kp = 1;
float ki = 0.1;
int setpoint =0;

// SET negative counter
void setLed()
{
  if(count <0){digitalWrite(Direction_PIN,HIGH);}
  else{digitalWrite(Direction_PIN,LOW);}
}

// SET 7Segment
void set7seg(int count)
{
  int num=count/100;
  if (num <= 99)
  {
  shiftOut(DATA_PIN,CLK_PIN,MSBFIRST,map7Seg[abs(num)/10]);
  digitalWrite(SS_PIN,HIGH);
  digitalWrite(SS_PIN,LOW);
  shiftOut(DATA_PIN,CLK_PIN,MSBFIRST,map7Seg[abs(num)%10]);
  digitalWrite(SS2_PIN,HIGH);
  digitalWrite(SS2_PIN,LOW);
  }
}

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


void setup()
{
  pinMode(aCH_PIN, INPUT_PULLUP);
  pinMode(bCH_PIN, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("Test Encoder");
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  pinMode(Direction_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLK_PIN,OUTPUT);
  pinMode(SS_PIN,OUTPUT);
  pinMode(SS2_PIN,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(aCH_PIN),aCH_Callback, RISING);
  attachInterrupt(digitalPinToInterrupt(bCH_PIN),bCH_Callback, RISING);
}

void loop()
{
  setpoint = map(analogRead(POT_PIN),0,1024,-9999,9999);
  int error = setpoint - count;
  int pid = kp*(float)(error) + ki*(float)(errori);
  errori+=error;
  setSpeed(pid); // pid = -255 --> 255
  setLed();
  Serial.print(setpoint);
  Serial.print(",");
  Serial.print(count);
  Serial.println();
  delay(100);
  
  if(Serial.available())
  {
    String inString = Serial.readString();
    setpoint = inString.toInt();
    Serial.println(setpoint);
  }
  set7seg(count);
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
