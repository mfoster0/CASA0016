# CASA0016 part of MSc CONNECTED ENVIRONMENTS
Water Quality Sensors

## Summary

For this piece of coursework, a water quality device was built. The end product uses sensors for pH, turbidity, dissolved oxygen and conductivity. The results of the measurements are displayed on an LCD screen for the user. The devive uses an Arduino MKR 1310.

## Keywords
Internet of Things, Connected Environments, Prototypying, Water Sensors

## Project Overview
The main objective initially was to have a deployable, standalone device that could sense and communicate current water quality. Due to time constraints, the scope was changed and a mobile device was built instead. Due to the initial direction being to deploy the device, some of the design decisions were driven by that and fitted around the later goal.

## Device in Action
https://github.com/mfoster0/CASA0016/blob/main/Images/WaterSensor.mp4
You may need to download the video. Current this one is too large for GitHub to play

## The Circuit
![Circuit](https://github.com/mfoster0/CASA0016/assets/63725574/56e7d74b-c70f-4213-8ef7-162a6e814f77)

The circuit is powered by a 3.7V LiPo battery through the JST with a latching switch to connect the power. 
The LCD connects to GND, VCC, SDA and SCL
The sensors connections are:
- Turbidity - A0, 5V and GND
- Dissolved Oxygen - A2, GND, 5V
- pH A4 GND, 5V
- Electrode A6 GND

## Sensors
Three sensors are off-the-shelf components that can be purchased from multiple manufactures. The datasheet should be used for your own configuration.
The conductivity sensor is built based on [https://www.instructables.com/Arduino-Water-Pollution-Monitor![image](https://github.com/mfoster0/CASA0016/assets/63725574/c087c075-4fbe-4cca-9e2d-b6af792cdfbd)](https://www.instructables.com/
Arduino-Water-Pollution-Monitor)https://www.instructables.com/Arduino-Water-Pollution-Monitor
** Note the variability on readings meant this sensor did not work to a point that it could be relied on for accurate readings
![TurbidityCustomisation](https://github.com/mfoster0/CASA0016/assets/63725574/9eb1e0f5-ba2d-4de2-9745-06e191fecc7f)

## Code
The code is straight forward. It constant iterates through sensors taking readings one sensors at a time every 5 seconds
The code is under the Code/WaterSamplerv3 folder
Sensor tester files are under Code/SensorTesters

Below is a sample read form one of the sensors 
void readpH(){
  static float pHValue,voltage;

  //take the reading
  int pHRead = analogRead(phSensorPin);
  readingsTaken++;

  //calculate the voltage based on 5 volts and a max value of 1024  
  voltage = pHRead*5.0/ADC_RES;

  // add the calibrated offset and use the DF robot sensor's coefficient 3.5 
  pHValue = 3.5*voltage+Offset;
  

  //set up output lines 1 and 2
  char* l1 = "pH"; 
  const char* l2 = floatToStr(pHValue).c_str();
 
  //write to screen
  writeToLCD(l1, l2, 0, 255, 0);
}

## The Enclosure
A laser cut ply box was used to house the electronics. It was designed to work like a toolbox. The board and LCD were kept on one side with the sensors contained on the other.

The board was housed in an IP55 rated enclosure to shield from any water splashed during sampling.

![OutsideClosed](https://github.com/mfoster0/CASA0016/assets/63725574/a6233607-cd88-4c3d-bdb7-bd8973760ef5)


## References used
1)	“Lee (Tottenham Locks to Bow Locks/Three Mills Locks) Water Body.” Lee (Tottenham Locks to Bow Locks/Three Mills Locks) | Catchment Data Explorer | Catchment Data Explorer, environment.data.gov.uk/catchment-planning/WaterBody/GB106038077852. Accessed 10 Jan. 2024. 
2)	Dissolved Oxygen in Water - Cdn.Cyfoethnaturiol.Cymru, cdn.cyfoethnaturiol.cymru/media/692076/new-information-note-dissolved-oxygen.pdf. Accessed 10 Jan. 2024. 
3)	“Water on the Web: Understanding: Water Quality: Parameters: Turbidity.” Water on the Web | Understanding | Water Quality | Parameters | Turbidity, waterontheweb.org/under/waterquality/turbidity.html. Accessed 10 Jan. 2024. 
4)	Ph | US EPA - U.S. Environmental Protection Agency, www.epa.gov/caddis-vol2/ph. Accessed 10 Jan. 2024. 
5)	Electrical Conductivity: Water Quality Parameters #6, Chapel Hill Local Government Video, 21 Oct. 2020, https://www.youtube.com/watch?v=5zQejvjaG7g. Accessed 10 Jan. 2024. 
6)	“Temperature and Water Completed.” Temperature and Water | U.S. Geological Survey, www.usgs.gov/special-topics/water-science-school/science/temperature-and-water. Accessed 10 Jan. 2024.
7)	Perovich, L. (no date) From data physicalization to data experiences:    combining art, science, technology, and community to move  towards collective action on environmental challenges. dissertation. 
8)	AlexisC47, and Instructables. “Arduino Water Pollution Monitor.” Instructables, Instructables, 28 Sept. 2017, www.instructables.com/Arduino-Water-Pollution-Monitor/. 
9)	Clarion UK, “IP Ratings Explained: Ingress Protection Rating: IP Codes: Updated 2022.” Clarion UK, 4 Oct. 2022, clarionuk.com/resources/ip-ratings. 
10)	“Attachinterrupt().” attachInterrupt() - Arduino Reference, www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/. Accessed 10 Jan. 2024. 
11)	Facchinm, “ArduinoLowPower.” GitHub, github.com/arduino-libraries/ArduinoLowPower/blob/master/examples/ExternalWakeup/ExternalWakeup.ino. Accessed 10 Jan. 2024. 
12)	 Ada, Lady. “All about Batteries.” Adafruit Learning System, learn.adafruit.com/all-about-batteries/power-capacity-and-power-capability. Accessed 10 Jan. 2024. 
13)	“How to Calculate Battery Run-Time.” How to Calculate Battery Run-Time When Design Equipment Using Batteries; Battery Technical Resources for Design Engineers from PowerStream, www.powerstream.com/battery-capacity-calculations.htm. Accessed 10 Jan. 2024. 

