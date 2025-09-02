#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include "time.h"

// Ultrasonic Sensor Pins
const int TRIG_PIN = 12;
const int ECHO_PIN = 14;

// SD Card
const int CS_PIN = 5;

// WiFi Credentials
const char* ssid = "realme 2 Pro";
const char* password = "12345678";

// NTP Server and Timezone Settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;  // IST (+5:30)
const int daylightOffset_sec = 0;

long duration;
float distance_cm;
File myFile;

void WriteFileWithTimestamp(const char* path, float distance) {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  myFile = SD.open(path, FILE_APPEND);
  if (myFile) {
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

    myFile.print("Time: ");
    myFile.print(timestamp);
    myFile.print(" - Distance: ");
    myFile.print(distance, 2);
    myFile.println(" cm");
    myFile.close();

    Serial.print("Time: "); Serial.print(timestamp);
    Serial.print(" - Distance: "); Serial.print(distance, 2); Serial.println(" cm");
  } else {
    Serial.println("Failed to open file for writing.");
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  delay(500);

  // Connect to WiFi
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Time sync
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Waiting for time...");
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTime synchronized.");

  // SD card
  Serial.println("Initializing SD card...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialized.");
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);  
  distance_cm = (duration * 0.0343) / 2;

  // Only log distances in the valid sensor range
  if (distance_cm >= 2 && distance_cm <= 400) {
    WriteFileWithTimestamp("/Sensor_data.txt", distance_cm);
  } else {
    Serial.println("Out of range");
  }

  delay(5000);  // Log every 5 seconds
}