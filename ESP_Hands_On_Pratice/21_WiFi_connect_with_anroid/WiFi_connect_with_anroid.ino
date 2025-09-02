/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <WiFi.h>

String  ClientRequest;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

void setup()
{
ClientRequest = "";

Serial.begin(9600);

pinMode(5, OUTPUT);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("realme 2 Pro","12345678");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest.remove(0, 5);
    ClientRequest.remove(ClientRequest.length()-9,9);
    ClientRequest = (ReadIncomingRequest());
    if (ClientRequest == "on") {
      digitalWrite(2,HIGH);

    }
    if (ClientRequest == "off") {
      digitalWrite(2,LOW);

    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>ESP32 Web Page</title></head>");
          client.println("<body>");
          client.println("<h1>Welcome to ESP32 Server</h1>");
          client.println("<p>This web page is served from my ESP32 board.</p>");
          client.println("<p>Created by: <strong>John</strong></p>");
          client.println("</body></html>");
    delay(1);

  client.flush();

}