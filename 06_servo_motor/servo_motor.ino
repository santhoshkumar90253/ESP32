#include <ESP32Servo.h>      // Include ESP32 Servo library

Servo myservo;               // Create a Servo object
const int servoPin = 13;     // Servo signal pin connected to GPIO 13

void setup() {
  myservo.attach(servoPin);  // Attach servo to the defined pin
}

void loop() {
  myservo.write(0);          // Move servo to 0 degrees
  delay(2000);               

  myservo.write(90);         // Move servo to 90 degrees
  delay(1000);               

  myservo.write(180);         // Move servo to 180 degrees
  delay(1000); 
} 