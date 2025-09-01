#include<WiFi.h>
#include<HTTPClient.h>

#define pot_u8 32
const char* ssid = "realme 2 Pro";
const char * pwd="12345678";

const char * servName = "http://api.thingspeak.com/update";
String apiKey = "XTCOXSST2WCS4EHG";

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid ,pwd);
  Serial.println("Connecting...");
  while(WiFi.status()!= WL_CONNECTED)
  {
	delay(500);
	Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi Network with IP Address: ");
  Serial.println(WiFi.local.IP());
  pinMode(pot_u8, INPUT);
}
void loop()
{
  if(WiFi.status()== WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;
    delay(10000);
    float f = analogRead(pot_u8);
    http.begin(client,servName);
    http.addHeader("Content-Type","application/x-www-form-urlencoded");
    String httpReqData = "api_key=" + apiKey + "&field1= " +string(f);
    int httpRespCode = http.POST(httpReqData);
    Serial.print("HTTP Response Code : ");
    Serial.println(httpRespCode);
    http.end();
  }
  else
  {
    Serial.println("WiFi - Disconnected");
  }
}