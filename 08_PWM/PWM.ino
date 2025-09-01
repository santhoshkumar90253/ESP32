const int led = 2;       
const int freq = 5000;       // PWM frequency = 5 kHz
const int resolution = 8;    // 8-bit resolution (0–255 duty cycle)

void setup() {
  // Attach LED pin to a PWM channel with given frequency and resolution
  if (!ledcAttach(led, freq, resolution)) 
  {
    while (1);  // Stop if PWM setup fails
  }
}

void loop() {
  // Increase brightness
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) 
  {
    ledcWrite(led, dutyCycle);  // Set PWM duty cycle
    delay(15);                  // Small delay for smooth fade
  }

  // Decrease brightness
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) 
  {
    ledcWrite(led, dutyCycle);  // Set PWM duty cycle
    delay(15);                  // Small delay for smooth fade
  }
}