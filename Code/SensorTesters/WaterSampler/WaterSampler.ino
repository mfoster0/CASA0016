#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"
#include <iostream>
#include <string>
#include <cstring>

Waveshare_LCD1602_RGB lcd(16, 2); //16 characters and 2 lines of show
//hold Turbidity Value
int turbReading = 0;

//dissolved oxygen
#define VREF    5000//VREF(mv)
#define ADC_RES 1024//ADC Resolution
uint32_t rawDO;

//electrode reading
int electrodeReading = 0;

//ph reading
#define phSensorPin A4            //pH meter Analog output to Arduino Analog Input 4
#define Offset -3.02            //deviation compensate after calibration


int readingsTaken = 0;
int readingsExpected = 4;

void setup() {
  // initialize
  lcd.init();

  lcd.clear();

  writeToLCD("Setting up", "Starting reads", 0, 255, 0);
  delay(5000);

}

void loop() {

  writeToLCD("Setting up", "Starting reads", 0, 255, 0);
  delay(3000);

  int i = 0;
  while (i < 2) {
    readingsTaken = 0;

    lcd.clear();
    readTurbidity();
    delay(5000);

    lcd.clear();
    readDO();
    delay(5000);

    lcd.clear();
    readElectrode();
    delay(5000);

    lcd.clear();
    readpH();
    delay(5000);
  }

  //send data

  //go back to sleep
  

}

void readElectrode(){
  electrodeReading = analogRead(A6);
  float volts = electrodeReading*(3.3/1023); //3.3V div by max value
  Serial.print("Conductivity: ");

  readingsTaken++;

  //write to screen
  char* l1 = "Conductivity ["; // + String(readingsTaken) + "/" + String(readingsExpected) + "]:").c_str();
  
  const char* l2 = floatToStr(volts).c_str();
  Serial.println(l2);
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);
  
}  
void readDO() {
  rawDO=analogRead(A2);
  Serial.println("Dis. O2 raw:\t"+String(rawDO)+"\tVoltage(mv)"+String(rawDO*VREF/ADC_RES));
  readingsTaken++;

  //write to screen
  char* l1 = "Dis. O2 ["; // + String(readingsTaken) + "/" + String(readingsExpected) + "]:").c_str();
  
  const char* l2 = intToStr(rawDO).c_str();
  Serial.println(l2);
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);
  
}

void readpH(){
  static float pHValue,voltage;

  int pHRead = analogRead(phSensorPin);
  readingsTaken++;
  Serial.println(pHRead);
  voltage = pHRead*5.0/1024;
  pHValue = 3.5*voltage+Offset;
  Serial.println(pHValue);

  //write to screen
  char* l1 = "pH ["; // + String(readingsTaken) + "/" + String(readingsExpected) + "]:").c_str();
  
  const char* l2 = floatToStr(pHValue).c_str();
  Serial.println(l2);
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);


}
void readTurbidity(){
  turbReading = analogRead(A0);
  Serial.println(turbReading);
  readingsTaken++;

  char* l1 = "Turbidity ["; // + String(readingsTaken) + "/" + String(readingsExpected) + "]:").c_str();
  
  const char* l2 = intToStr(turbReading).c_str();
  Serial.println(l2);
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);
  
  //write to LoRa packet  

}  


std::string floatToStr(float theFloat){
    // Convert the float to a std::string
    std::string floatAsString = std::to_string(theFloat); 

    return floatAsString;
}

std::string intToStr(int theInt){

    // Convert the integer to a std::string
    std::string intAsString = std::to_string(theInt); 

    return intAsString;
}
void writeToLCD(char* line1, const char* line2, int r, int g, int b){

  lcd.setRGB(r, g, b);
  lcd.setCursor(0, 0);
  lcd.send_string(line1);
  lcd.setCursor(0, 1);
  lcd.send_string(line2);
}


