#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define POT_u8 32
#define OLED_W_u16 128
#define OLED_H_u8 64
#define SCREEN_Addr_u8 0x3C 
#define OLED_RESET_i8 -1
#define textSize_u8 1
Adafruit_SSD1306 display(OLED_W_u16, OLED_H_u8, &Wire, OLED_RESET_i8);
void setup() 
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_Addr_u8)) {
    Serial.println(F("oLED Module not Found!"));
    for(;;);                          
  }
  delay(3000);
  display.clearDisplay();
  display.setTextSize(textSize_u8);             
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);             
  display.println(F("Potentio Meter :"));
  display.display();
  delay(2000);
}
void loop() {
  uint16_t potVal = analogRead(POT_u8);
  display.fillRect(0, 10, OLED_W_u16, 10, SSD1306_BLACK);
  display.setCursor(0, 10);           
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE); 
  display.print("Pot Value: ");
  display.println(potVal);            
  display.display();
}