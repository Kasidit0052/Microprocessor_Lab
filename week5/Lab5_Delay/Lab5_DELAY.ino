
#define LEDPIN 9
int timeCount=0;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  delay(1000);
  Serial.print("Start:");
  Serial.println();
}

void loop() 
{ 
  if(timeCount<=120)
  {
  digitalWrite(LEDPIN,HIGH); 
  delay(1000);
  timeCount++;
  digitalWrite(LEDPIN,LOW); 
  delay(1000);
  timeCount++;
  Serial.print("secondCount:");
  Serial.print(timeCount, DEC);
  Serial.println();
  }
  else
  {
    Serial.print("timeStop!");
    Serial.println();
  }
  
}
// Duration 2.02 seconds 
// using arduino delay is slower because arduino has multiple library
// which might affect searching and computing time
