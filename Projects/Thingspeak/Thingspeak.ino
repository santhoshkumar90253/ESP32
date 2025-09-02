#include <WiFi.h>
#include <HTTPClient.h>

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;

const char* ssid = "realme 2 Pro";
const char* password = "12345678";

String apiKey = "XTCOXSST2WCS4EHG";
const char* server = "http://api.thingspeak.com/update";

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  long duration;
  float distance_cm;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration * 0.034 / 2;

  if (distance_cm <= 0 || distance_cm > 400) 
  {
    Serial.println("Invalid distance reading");
    delay(15000);
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    String url = server;
    url += "?api_key=" + apiKey;
    url += "&field1=" + String(distance_cm);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) 
    {
      Serial.print("ThingSpeak Response Code: ");
      Serial.println(httpCode);
    } 
    else 
    {
      Serial.println("Error sending data to ThingSpeak");
    }
    http.end();
  }

  delay(2000);
}