void setup() {
  Serial.begin(115200);  // Initialize serial Monitor communication 
}

void loop() {
  int measurement = 0;           // To store hall sensor value

  measurement = hallRead();     // Read built-in Hall effect sensor on ESP32
  
  Serial.println(measurement);  // Print measured value

  delay(1000);  
}