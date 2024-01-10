// Water tester code
// The code uses 4 sensors (pH, Turbidity, Dissolved Oxygen and conductivity)
// This version writes data to an LCD screen whereas originally this was intended to write to the QEOP LoRa router 
// It is for a manually activated water testing device and is carried by the user meaning the low power deep sleep functions origin
// A powerbank is carried with device which no longer requires the extremely lower consumption approach first deign and simple delays
// can be used without concern of them being less power efficient.
// example code has been used from component manufactor's sites and online available arduino examples 
// https://www.waveshare.com/wiki/LCD1602_RGB_Module
// https://forum.arduino.cc/t/arduino-nano-and-waveshare-lcd1602-rgb/976673 
// https://wiki.dfrobot.com/PH_meter_SKU__SEN0161_
// https://how2electronics.com/diy-turbidity-meter-using-turbidity-sensor-arduino/
// https://how2electronics.com/dissolved-oxygen-sensor-arduino-interfacing-tutorial/
//
// author: Mark Foster


#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"
#include <iostream>
#include <string>
#include <cstring>

//configure lcd display set up
Waveshare_LCD1602_RGB lcd(16, 2); //16 characters and 2 lines of show
//hold Turbidity Value
int turbReading = 0;

//dissolved oxygen
#define VREF    5000//VREF(mv) 
#define ADC_RES 1024//ADC Resolution (max value)
uint32_t rawDO; // raw value

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

  //inform user reading are about to start
  writeToLCD("Setting up", "Starting reads", 0, 255, 0);
  delay(5000);

}

// call each of the sensors sequentially, allow user enough time to note the readings
void loop() {

  //when using in an automated mode, the device would wake, take 2 sets of readings, post to the remote router and go back to sleep
  //now this stays as a constanty loop until the user powers the device down
  int i = 0;
  while (i < 2) {
    //used for understanding what data should be sent via LoRa 
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
  // send via LoRa

  //go back to sleep
  // enter deep sleep again

}

//Only the board's logic voltage is used for the electrode read
void readElectrode(){
  electrodeReading = analogRead(A6);
  float volts = electrodeReading*(3.3/ADC_RES); //3.3V div by max value
  Serial.print("Conductivity: ");

  readingsTaken++;

  //write to screen
  char* l1 = "Conductivity ["; // + String(readingsTaken) + "/" + String(readingsExpected) + "]:").c_str();
  
  const char* l2 = floatToStr(volts).c_str();
  Serial.println(l2);
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);
  
}  

// read dissolved oxygen
// reading taken using the sensor with raw value adjust with milli-volts and the max analogue value (1024)
void readDO() {
  rawDO=analogRead(A2);
  Serial.println("Dis. O2 raw:\t"+String(rawDO)+"\tVoltage(mv)"+String(rawDO*VREF/ADC_RES));
  readingsTaken++;

  //write to screen
  char* l1 = "Dis. O2 ["; // + String(readingsTaken) + "/" + String(readingsExpected) + "]:").c_str();
  
  //const char* l2 = intToStr(rawDO).c_str(); //keep incase raw value preferred
  const char* l2 = floatToString(rawDO*VREF/ADC_RES);
  Serial.println(l2);
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);
  
}

//
void readpH(){
  static float pHValue,voltage;

  //take the reading
  int pHRead = analogRead(phSensorPin);
  readingsTaken++;
  Serial.println(pHRead);
  //calculate the voltage based on 5 volts and a max value of 1024  
  voltage = pHRead*5.0/ADC_RES;
  // add the calibrated offset and use the DF robot sensor's coefficient 3.5     
  pHValue = 3.5*voltage+Offset;
  Serial.println(pHValue);

  //set up output lines 1 and 2
  char* l1 = "pH "; 
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

//float to string converter
std::string floatToStr(float theFloat){
    // Convert the float to a std::string
    std::string floatAsString = std::to_string(theFloat); 

    return floatAsString;
}

// int to string converter
std::string intToStr(int theInt){

    // Convert the integer to a std::string
    std::string intAsString = std::to_string(theInt); 

    return intAsString;
}

//write to screen
void writeToLCD(char* line1, const char* line2, int r, int g, int b){

  lcd.setRGB(r, g, b);
  lcd.setCursor(0, 0);
  lcd.send_string(line1);
  lcd.setCursor(0, 1);
  lcd.send_string(line2);
}


