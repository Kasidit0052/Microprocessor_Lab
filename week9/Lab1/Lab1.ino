#define LED_PIN 8
#define SW_PIN 2
bool buttonStatus=true;
int mode=1;

void blinkLED(int mode)
{
  if(mode ==1){digitalWrite(LED_PIN,LOW);delay(500);digitalWrite(LED_PIN,HIGH);delay(500);}
  if(mode ==2){digitalWrite(LED_PIN,LOW);delay(1000);digitalWrite(LED_PIN,HIGH);delay(1000);}
  if(mode ==3){digitalWrite(LED_PIN,LOW);delay(1500);digitalWrite(LED_PIN,HIGH);delay(1500);}
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_PIN),ISR_Callback, RISING);
}

void loop()
{
  blinkLED(mode);
}

void ISR_Callback()
{
  mode++;
  if(mode>3){mode=1;}
  Serial.println(mode);
} 
