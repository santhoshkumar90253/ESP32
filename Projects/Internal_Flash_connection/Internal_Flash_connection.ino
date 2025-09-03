#include <SPIFFS.h>
#include"FS.h"
#include"SPIFFS.h"
#include "time.h"
#include <WiFi.h>


#define UT_trig_u8 5
#define UT_echo_u8 18
File ut_file;

const char* ssid = "realme 2 Pro";
const char* password = "12345678";

// NTP Server and Timezone Settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;  // IST (+5:30)
const int daylightOffset_sec = 0;
void utDataWriteInFlash(const char *path, float dist) 
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) 
  {
    Serial.println("Failed to obtain time");
    return;
  }

  ut_file = SPIFFS.open(path, FILE_APPEND);
  if (ut_file) 
  {
    Serial.println("\nUploading...");
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

    ut_file.print("Time: ");
    ut_file.print(timestamp);
    ut_file.print("  Distance: ");
    ut_file.print(dist);
    ut_file.println(" cm");
    ut_file.close();
  } 
  else 
  {
    Serial.println("Failed to open file for writing.");
  }
}
void readIntFlashData(const char *path)
{
  File file = SPIFFS.open(path, "r"); // Open in read mode
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  while (file.available()) {
    String line = file.readStringUntil('\n');  // Read until newline
    Serial.println(line);
  }
}
void setup() {

  Serial.begin(9600);
  // SPIFFS
   if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  if (SPIFFS.exists("/ut_data.txt")) {
    Serial.println("File exists. Deleting...");

    // Delete the file
    if (SPIFFS.remove("/ut_data.txt")) {
      Serial.println("File deleted successfully.");
    } else {
      Serial.println("Failed to delete the file.");
    }
  }
  // UT .. 
  pinMode(UT_trig_u8,OUTPUT);
  pinMode(UT_echo_u8,INPUT);
   // Connect to WiFi
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Time sync
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Waiting for time...");
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTime synchronized.");
}

void loop() {
   digitalWrite(UT_trig_u8,LOW);
  delay(2);
  digitalWrite(UT_trig_u8,HIGH);
  delay(10);
  digitalWrite(UT_trig_u8,LOW);
  
  uint32_t time = pulseIn(UT_echo_u8,HIGH);
  uint32_t dist = (time /2.0)/29.1;
  // Serial.println("\n Dist : ");
  // Serial.println(dist);
  if( (dist > 5) && (dist < 40) )
  {
    utDataWriteInFlash("/ut_data.txt",dist);
    //delay(500);
    readIntFlashData("/ut_data.txt");
  }
}