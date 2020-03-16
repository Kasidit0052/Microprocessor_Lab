#define POT_PIN A0
int potValue;

void setup()
{
  Serial.begin(9600);
  while (!Serial){;}
}

void loop()
{
  potValue=analogRead(POT_PIN);
  Serial.println(potValue);
  delay(300);
}
