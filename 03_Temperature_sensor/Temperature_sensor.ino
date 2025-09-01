#include<DHT.h>

DHT dht2(2, DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Temperature");
  Serial.println((dht2.readTemperature()));
  Serial.println("Humidity");
  Serial.println((dht2.readHumidity()));
}
