//#include <LiquidCrystal_I2C.h> //Download the library below 
#include <Wire.h>

//LiquidCrystal_I2C lcd(0x3F,16,2); //Set 0x27 if your using different i2c address (20,4 if your using 20/4 LCD)
int pHSense = A0;
int tempSense = 8;
void setup() {

  Serial.begin(9600);
  delay(100);

  pinMode(tempSense, INPUT);    // sets the digital pin 8 as input

  //Wire.begin(2,14);
  //lcd.init();
  //lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.print("14CORE | pH Probe ");
  //lcd.setCursor(0,1);
  //lcd.print(">Initializing...");
  //delay(4000);
  // lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("14CORE | pH Sense");
  Serial.println("14CORE | pH Sense");
  
}

void loop(){
    int measuringVal = analogRead(pHSense);
    Serial.print("Measuring Raw Value > ");
    Serial.print(measuringVal);

    double vltValue = 5/1024.0 * measuringVal;
    Serial.print("Voltage Value: ");
    Serial.print(vltValue, 3);

    float P0 = 7 + ((2.5 - vltValue) / 0.18);
    Serial.println("");
    Serial.print("pH Value: ");
    Serial.print(P0, 3);
    Serial.println("");

    float curTemp = digitalRead(tempSense);

    Serial.print("Temp Value: ");
    Serial.print(curTemp, 3);
    Serial.println("");
 
    delay(3000);
}