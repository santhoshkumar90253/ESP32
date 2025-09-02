#include <Wire.h>                     // I2C communication library
#include <Adafruit_GFX.h>            // Graphics library
#include <Adafruit_SSD1306.h>        // OLED display library

#define SCREEN_WIDTH 128             // OLED width in pixels
#define SCREEN_HEIGHT 64             // OLED height in pixels

// Create display object with I2C and no reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int count = 0;                    

void setup() {
  // Initialize OLED display with I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("OLED not found"));  // Print error if not found
    for (;;);                             // Stop if display not found
  }

  display.clearDisplay();                 // Clear the display
  display.setTextSize(1);                 // Set text size to 1x
  display.setTextColor(SSD1306_WHITE);    // Set text color to white
  display.setCursor(0, 0);               // Set cursor position
  display.println("Hello");              // Print first line
  display.display();                      // Show content on screen
}

void loop() {
  count++;                              
}