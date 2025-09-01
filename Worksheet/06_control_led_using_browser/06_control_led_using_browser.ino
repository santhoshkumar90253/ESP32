#include <WiFi.h>  // Include WiFi library for ESP32

// Wi-Fi credentials
const char* ssid     = "realme 2 Pro";       // Your Wi-Fi network name
const char* password = "12345678";       // Your Wi-Fi password
#define led_u8  2
WiFiServer server(80);  // Create a server on port 80 (default HTTP)

void setup() {
  Serial.begin(9600);                 // Start serial monitor at 115200 baud
  WiFi.begin(ssid, password);          // Connect to Wi-Fi network
  pinMode(led_u8, OUTPUT);
  digitalWrite(led_u8,LOW);
  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");                 // Print dots while connecting
  }

  Serial.println();                    // Line break
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());      // Print ESP32 local IP address

  server.begin();                      // Start the server
}

void loop() {
  WiFiClient client = server.available();  // Check for incoming client

  if (client) {
    String ledStatus = "";            // To store the HTTP request

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        ledStatus += c;

        if (c == '\n') {  // End of HTTP request line

          break;  // Break after sending response
        }
      }
    }
    if (ledStatus.endsWith("GET /on") != -1) {
      digitalWrite(led_u8, HIGH);  // Turn ON LED
      Serial.println("LED turned ON");
    }
    else if (ledStatus.endsWith("GET /off") != -1) {
      digitalWrite(led_u8, LOW);   // Turn OFF LED
      Serial.println("LED turned OFF");
    }
    // Send HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // Send custom HTML content
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head><title>ESP32 Web Page</title></head>");
          client.println("<body>");
          client.println("<h1>Welcome to ESP32 Server</h1>");
          client.println("<p>This web page is served from my ESP32 board.</p>");
          client.println("<p>Created by: <strong> JOHN </strong></p>");
          client.println("</body></html>");
    delay(1);       // Small delay before closing connection
    client.stop();  // Disconnect the client
  }
}