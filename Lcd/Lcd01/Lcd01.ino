#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup(){
  Serial.begin(115200);
  Serial.println("setup()"); //called twice after flashing from Arduino IDE!!!???
  lcd.begin(16,2);
}

void loop(){
  lcd.setCursor(0, 0);
  lcd.print("hello!");
}
