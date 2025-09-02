#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();  // Declare internal temperature sensor function - treat it as C function
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();  // Declare function 

void setup() {
  Serial.begin(115200);  // Start serial Monitor communication
}

void loop() {
  Serial.print("Temperature: ");

  // Read internal temperature sensor, convert from Fahrenheit to Celsius
  Serial.print((temprature_sens_read() - 32) / 1.8);  
  Serial.println(" C");  // Print temperature in Celsius

  delay(5000);  
}