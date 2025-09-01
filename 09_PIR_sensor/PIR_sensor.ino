#define PIR_PIN 15    
#define LED_PIN 2     

void setup() {
  pinMode(PIR_PIN, INPUT);    // Set PIR pin as input
  pinMode(LED_PIN, OUTPUT);   // Set LED pin as output
}

void loop() {
  int motion = digitalRead(PIR_PIN);  // Read motion from PIR sensor

  if (motion == HIGH) 
  {
    digitalWrite(LED_PIN, HIGH);      // Turn ON LED if motion detected
  } 
  else 
  {
    digitalWrite(LED_PIN, LOW);       // Turn OFF LED if no motion is detected
  }

  delay(500);  
}