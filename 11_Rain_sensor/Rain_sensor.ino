#define DO_PIN 16      // Digital output pin from rain sensor

void setup() {
  Serial.begin(9600);           
  pinMode(DO_PIN, INPUT);       // Set digital output pin as input
}

void loop() {
  int rain_state = digitalRead(DO_PIN); // Read sensor value

  if (rain_state == HIGH)
    Serial.println("The rain is NOT detected"); // No rain
  else
    Serial.println("The rain is detected");     // Rain detected

  delay(1000); 
}