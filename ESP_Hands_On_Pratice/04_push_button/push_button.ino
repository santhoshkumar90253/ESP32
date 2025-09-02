#define LED 2
#define button 4

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  if (digitalRead(button) == LOW)
  {
    digitalWrite(LED, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(LED, LOW);
    delay(500);
  }
}
