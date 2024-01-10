#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"

Waveshare_LCD1602_RGB lcd(16, 2); //16 characters and 2 lines of show
int r, g, b, t = 0;

void setup() {
  // initialize
  lcd.init();

  lcd.clear();
}

void loop() {
  r = 255;
  g = 0;
  b = 0;
  t = t + 3;
  lcd.setRGB(r, g, b);
  lcd.setCursor(0, 0);
  lcd.send_string("Waveshare");
  lcd.setCursor(0, 1);
  lcd.send_string("Hello,World!");
  delay(1000);
  lcd.clear();
}
