#include <SPI.h>
#include <SPIFlash.h>
#include "time.h"
#include <WiFi.h>
#include "time.h"
#include<Wire.h>

#define ext_flash_cs_u8 5  // cs pin for ext flash
#define ext_flash_base_addr_u8 0 // ext flash starting addr
#define ext_flash_size_u16 (2*1024) // ext flash size 

#define UT_trig_u8 12
#define UT_echo_u8 13
int c=0;
//******************Flash***********************
SPIFlash flash(ext_flash_cs_u8);  
uint32_t pc_u32 = 0;
String  data;
char sndData[70], rcvData[70];

//******************WIFI***********************

const char* ssid = "realme 2 Pro";
const char* password = "12345678";

//******************TIME***********************
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;  
const int daylightOffset_sec = 0;
char timestamp[30];
void writeReadDataExtFlash(float dist)
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) 
  {
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);
  data ="Time: " + String(timestamp) + " Distance: " + String(dist) + " cm";
  data.toCharArray(sndData, sizeof(sndData));
   
  if (pc_u32 <= ext_flash_base_addr_u8 + ext_flash_size_u16) 
  {
    if(dist> 20.0 && dist <40.0)
    {
      flash.writeBytes(pc_u32, sndData, strlen(sndData)+1);
      flash.readBytes(pc_u32,rcvData, sizeof(rcvData));
      pc_u32+=strlen(sndData)+1;
      Serial.print(" ");
      Serial.println(rcvData);
      delay(1000);
    }
  }   
  else
  {
    
    pc_u32 = ext_flash_base_addr_u8;
    Serial.println(ext_flash_base_addr_u8 + ext_flash_size_u16);
    flash.chipErase();
    Serial.println("Empty Flash");
    delay(1000);
  }
   
}
float ultraSonicData(void)
{
  digitalWrite(UT_trig_u8,LOW);
  delay(2);
  digitalWrite(UT_trig_u8,HIGH);
  delay(10);
  digitalWrite(UT_trig_u8,LOW);
  uint32_t time = pulseIn(UT_echo_u8,HIGH);
  float dist = (time /2.0)/29.1;
  return dist;
}
void setup() {
  Serial.begin(9600);
  SPI.begin();
  delay(2000);
//******************FLASH***********************
  if (!flash.initialize()) {
    Serial.println("Flash memory initialization failed!");
    while (1) Serial.print(".");
  }
  flash.chipErase();
   //******************UT*********************** 
  pinMode(UT_trig_u8,OUTPUT);
  pinMode(UT_echo_u8,INPUT);

  //******************WIFI***********************
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

 //******************TIME***********************
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
  
  float dist = ultraSonicData();
  writeReadDataExtFlash(dist);
}