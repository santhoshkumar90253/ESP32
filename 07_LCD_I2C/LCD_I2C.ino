#include <LiquidCrystal_I2C.h> // adding LCD-I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2); //creating object of lcd_I2C

void setup() {
  lcd.init();        // Initialize LCD
  lcd.backlight();   // Turn on the backlight
}

void loop() {
  lcd.clear();   //To clear the display
  lcd.setCursor(0, 0);//setting cursor posiiton
  lcd.print("Hello"); //transmitting the content via I2C to LCD
  lcd.setCursor(0, 1); 
  lcd.print("World");
  delay(2000);
}