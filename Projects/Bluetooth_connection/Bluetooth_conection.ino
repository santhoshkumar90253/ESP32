#include "BluetoothSerial.h" 
#include "time.h" // Include Bluetooth Serial library
const int TRIG_PIN = 5;     // Trigger pin
const int ECHO_PIN = 18;    // Echo pin
BluetoothSerial SerialBT;     // Create an object of BluetoothSerial
// NTP Server and Timezone Settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;  // IST (+5:30)
const int daylightOffset_sec = 0;

void setup() {
  Serial.begin(9600);   
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);            // Start serial communication with PC 
  SerialBT.begin("ESP32_bluetooth");  // Start Bluetooth with device name "ESP32_bluetooth"
  Serial.println("Device started, now you can pair it with bluetooth!");
   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Waiting for time...");
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTime synchronized.");
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

  struct tm timeinfo;
  getLocalTime(&timeinfo);
    /*if (!) {
      Serial.println("Failed to obtain time");
      return;
    }*/

  char timestamp[30];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

  Serial.print("\nDate: ");
  Serial.println(timestamp);
  Serial.print(" Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  
  SerialBT.print("Distance: ") ;
  SerialBT.print(distance_cm);
  SerialBT.println(" cm");
  delay(20); 
}