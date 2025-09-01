const int LED = 2;
const int touch_pin = 14;
int touch_val, threshold = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  touch_val= touchRead(touch_pin);
  Serial.println(touch_val);
  if(touch_val > threshold)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);

    delay(500);
}
