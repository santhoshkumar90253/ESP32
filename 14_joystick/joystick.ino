#define VRX_PIN  39  //  GPIO 39 (ADC) for the X-axis of the joystick
#define VRY_PIN  36  //  GPIO 36 (ADC) for the Y-axis of the joystick

int X = 0;  // To store the analog value from X-axis
int Y = 0;  // To store the analog value from Y-axis

void setup() {
  Serial.begin(9600);                     // Initialize Serial Monitor communication
  analogSetAttenuation(ADC_11db);         // Set ADC attenuation to 11dB to read up to 0-3.3V
}

void loop() {
  X = analogRead(VRX_PIN);           // Read analog value from X-axis pin (0–4095)
  Y = analogRead(VRY_PIN);           // Read analog value from Y-axis pin (0–4095)

  Serial.print("x = ");                   
  Serial.print(X);                   // Print the X-axis value
  Serial.print("  y = ");                 
  Serial.println(Y);                 // Print the Y-axis value 

  delay(200);                             
}