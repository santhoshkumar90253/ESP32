/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <WiFi.h>

void setup()
{
Serial.begin(9600);

  WiFi.disconnect();
  delay(1000);
  Serial.println("program started");
  WiFi.begin("BITSILICA_1");
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print("...");
    delay(300);
    Serial.println("I am connected");
    Serial.println("IP ADDRESS");
    Serial.println((WiFi.localIP()));
  }

}


void loop()
{


}