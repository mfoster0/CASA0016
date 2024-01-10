const int buttonPin = 13;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // 50 milliseconds

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);

  //use delay to debouce the signal
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // debounce checker
  if ((millis() - lastDebounceTime) > debounceDelay) {
    //Serial.print("in checker");
    // genuine signal if not the same
    if (reading != lastButtonState) {
      Serial.print("Last btn state different");
      lastButtonState = reading;

      if (reading == LOW) {
        // The button is pressed
        Serial.print("Button Pressed");
      }
    }
  }

  lastButtonState = reading;
}