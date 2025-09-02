const int TRIG_PIN = 12;     // Trigger pin
const int ECHO_PIN = 14;    // Echo pin
const int LED_PIN = 2;      // LED output

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  long duration, distance_cm;

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration / 29 / 2; // Convert to cm

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Blink rate based on distance
  int blinkDelay;

  if (distance_cm < 10) {
    blinkDelay = 100; // very fast
  } else if (distance_cm < 30) {
    blinkDelay = 300; // medium fast
  } else if (distance_cm < 60) {
    blinkDelay = 700; // slower
  } else {
    blinkDelay = 1000; // slowest
  }
  // Blink the LED
  digitalWrite(LED_PIN, HIGH);
  delay(blinkDelay);
  digitalWrite(LED_PIN, LOW);
  delay(blinkDelay);
}