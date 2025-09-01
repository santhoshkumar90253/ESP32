/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

String  Data;
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
void printDeviceAddress() {

const uint8_t* point = esp_bt_dev_get_address();

for (int i = 0; i < 6; i++) {
   char str[3];
   sprintf(str, "%02X", (int)point[i]);
   Serial.print(str);
   if (i < 5){
   Serial.print(":");}
}
Serial.println();
}

void setup()
{
Data = "";

Serial.begin(9600);

pinMode(2, OUTPUT);
  delay(1000);
  SerialBT.begin("ESP32test");
  Serial.println("This is your address");
  printDeviceAddress();

}


void loop()
{

    if (SerialBT.available()) {
      Data = (SerialBT.readString());
      Serial.println(Data);
      if (Data == "ON") {
        digitalWrite(2,HIGH);

      }
      if (Data == "OFF") {
        digitalWrite(2,LOW);

      }

    }

}