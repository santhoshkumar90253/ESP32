#define pot_u8 32
void setup()
{
  pinMode(pot_u8, INPUT);
  Serial.begin(9600);
}
void loop()
{
  uint16_t potOp= analogRead(pot_u8);
  Serial.print("Pot Output :- ");
  Serial.println(potOp);
}