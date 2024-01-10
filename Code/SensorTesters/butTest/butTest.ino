const int buttonPin = 13;

int buttonState = 0;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(buttonPin, INPUT);
}

void loop() {
  delay(100);
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    Serial.println("on");
  } else {
    Serial.println("off");
  }
}