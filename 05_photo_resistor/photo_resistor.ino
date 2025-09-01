void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(2));//Reading Value from Pin 2 to which sensor is connected
  delay(1000);
}