void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println((touchRead(T0)));
  delay(1000);
}