
int electrodeReading = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  electrodeReading = analogRead(A6);
  float volts = electrodeReading*(3.3/1023);
  Serial.print("Conductivity: ");
  Serial.print(volts, 5);
  Serial.println("");
  delay(5000);
}
