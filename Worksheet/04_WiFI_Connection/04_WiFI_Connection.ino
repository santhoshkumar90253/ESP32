#include <WiFi.h>  // Include the WiFi library for ESP32

// Replace with your Wi-Fi credentials
const char* ssid = "realme 2 Pro";        // Your Wi-Fi network name (SSID)
const char* password = "12345678";  // Your Wi-Fi password

void setup() {
  Serial.begin(9600);      // Initialize serial communication at 9600 baud
  delay(1000);             // Short delay to allow everything to stabilize

  Serial.println("Connecting to WiFi ..");

  WiFi.begin(ssid, password);  // Start connecting to the Wi-Fi network

  // Keep checking connection status until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);           // Wait for half a second
    Serial.print(".");    // Print dots to show progress
  }

  // Once connected, print success message and IP address
  Serial.println();                        // Print a new line
  Serial.println("WiFi Connected!");       // Confirmation message
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());          // Show the ESP32's local IP address
}

void loop() {
  // Nothing in the loop yet — this runs repeatedly after setup()
}