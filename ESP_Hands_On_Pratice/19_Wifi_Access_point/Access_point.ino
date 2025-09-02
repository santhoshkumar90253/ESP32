#include<WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3000);
  Serial.println("START");
  WiFi.softAP("EncryptedNetwork", "Santhosh");
  Serial.println("The IP of the access point is : ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("The number of connected station: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(5000);
}
