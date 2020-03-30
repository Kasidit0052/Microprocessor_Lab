#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6
#define aCH_PIN 2
#define bCH_PIN 3
int map_vel;
int count = 0,encoder_status=0;
bool aCH_value,bCH_value,display_status=false;

void turn(int vel)
{
  //CW direction
  if(vel>0 && vel<=100)
  {
    map_vel = map(vel,0,255,0,100);
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH);
    analogWrite(MOTOR_PWM_PIN,vel);
  }
  
  //CCW direction
  else if(vel<0 && vel>=-100)
  {
    vel=-vel;
    map_vel = map(vel,0,255,0,100);
    digitalWrite(MOTOR_D1_PIN,HIGH);
    digitalWrite(MOTOR_D2_PIN,LOW);
    analogWrite(MOTOR_PWM_PIN,vel);    
  }
  
  else{digitalWrite(MOTOR_D1_PIN,LOW);digitalWrite(MOTOR_D2_PIN,LOW);}
}

void setup()
{
  pinMode(aCH_PIN, INPUT_PULLUP);
  pinMode(bCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Test Encoder");
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(aCH_PIN),aCH_Callback, RISING);
  attachInterrupt(digitalPinToInterrupt(bCH_PIN),bCH_Callback, RISING);
}

void loop()
{
  turn(-100); //change velocity here
  delay(100);
  if(encoder_status==1 && display_status == false){Serial.println("Clockwise direction");display_status=true;}
  if(encoder_status==2 && display_status == false){Serial.println("Anti-Clockwise direction");display_status=true;}
  Serial.print("count:");
  Serial.print(count);
  Serial.println();
}

void aCH_Callback()
{
  bool bCH_value=digitalRead(bCH_PIN);
  if(bCH_value==false)
  {
    encoder_status=1;
    count++;
  }
} 

void bCH_Callback()
{
  bool aCH_value=digitalRead(aCH_PIN);
  if(aCH_value==false)
  {
    encoder_status=2;
    count++;
  }
} 
