
/* based around the ArduinoLowPower library example. 
   changes to debounce the switch and reduce double clicking do not work, although the logic appears correct

/*
  ExternalWakeup

  This sketch demonstrates the usage of External Interrupts (on pins) to wakeup a chip in sleep mode.
  Sleep modes allow a significant drop in the power usage of a board while it does nothing waiting for an event to happen. Battery powered application can take advantage of these modes to enhance battery life significantly.

  In this sketch, shorting pin 8 to a GND will wake up the board.
  Please note that, if the processor is sleeping, a new sketch can't be uploaded. To overcome this, manually reset the board (usually with a single or double tap to the RESET button)

  This example code is in the public domain.
*/

#include "ArduinoLowPower.h"

// Blink sequence number
// Declare it volatile since it's incremented inside an interrupt
volatile int repetitions = 1;

// Pin used to trigger a wakeup
const int btnPin = 8;
const int ledPin = 5;
unsigned long lastUpdate = 0;
unsigned long btnInterval = 1500; //min millis between presses
bool update = false;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // Set pin 8 as INPUT_PULLUP to avoid spurious wakeup
  //pinMode(btnPin, INPUT_PULLUP);
  
  // Attach a wakeup interrupt on pin 8, calling repetitionsIncrease when the device is woken up
  //LowPower.attachInterruptWakeup(btnPin, repetitionsIncrease, CHANGE);
  lastUpdate = millis();
  btnInterval = 1500;

}

void loop() {
  if (update) { //}  &&   (millis() - lastUpdate) > btnInterval){
    repetitions ++;
    executeActions();
    // perform actions for wake state
    update = false;
    lastUpdate = millis();
  }
  // Triggers an infinite sleep (the device will be woken up only by the registered wakeup sources)
  // The power consumption of the chip will drop consistently
  LowPower.sleep();
}

void executeActions() {
  
  for (int i = 0; i < repetitions; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

void repetitionsIncrease() {
  // This function will be called once on device wakeup
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context
  
  update = true;
}