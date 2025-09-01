#define RELAY_PIN 16   // Relay connected to GPIO 16

void setup() {
  pinMode(RELAY_PIN, OUTPUT);  // Set relay pin as output
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH);  // Turn ON relay - the device connected to it will also turn-on
  delay(1000);                    
  digitalWrite(RELAY_PIN, LOW);   // Turn OFF relay
  delay(1000);                   
}