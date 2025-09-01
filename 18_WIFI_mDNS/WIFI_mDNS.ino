#include <WiFi.h>        // Include WiFi library for ESP32
#include <ESPmDNS.h>     // Include mDNS library to use hostnames like esp32.local

void setup() {
  Serial.begin(9600);         // Start serial communication at 115200 baud rate

  // Connect to Wi-Fi
  WiFi.begin("SANTHOSH", "12345678");   // Replace with your actual Wi-Fi credentials

  // Wait until connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");           // Print dots to indicate waiting
  }

  Serial.println();              // Newline after successful connection
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print the IP address assigned to ESP32

  // Start mDNS service with the name "esp32"
  if (MDNS.begin("Test")) {
    Serial.println("mDNS responder started");  // Success message
    // Now you can access the ESP32 using http://Test.local
  } else {
    Serial.println("Error setting up mDNS");   // Error message if mDNS fails
  }
}

void loop() {
  // Your main code will go here (if needed)
}