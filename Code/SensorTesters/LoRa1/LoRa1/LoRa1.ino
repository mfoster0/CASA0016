// First install "DHT sensor library" via the Library Manager
//#include <DHT.h>
#include <MKRWAN.h>

#define debugSerial Serial
#define DHTPIN 2  //Digital Pin 2
#define DHTTYPE DHT22

// Set your AppEUI and AppKey
const char *appEui = "0000000000000000";
const char *appKey = "1DC3F193FD1F0B8CE52E2A4363A380EB";

//DHT dht(DHTPIN, DHTTYPE);
LoRaModem modem;

void setup(){

  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  //Initialise the DHT sensor
  //dht.begin();

  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
  }
 
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
  }

}


void loop(){
  Serial.println("-- LOOP");


  //converting value to unsigned int for LoRa transmission
  //uint16_t humidity = 100*dht.readHumidity(false);
  uint16_t humidity = 7040;

  // false: Celsius (default)
  // true: Farenheit
  //converting value to unsigned int for LoRa transmission
  uint16_t temperature = 2050; //100*dht.readTemperature(false);

  // Split both words (16 bits) into 2 bytes of 8
  byte payload[4];
  payload[0] = highByte(temperature);
  payload[1] = lowByte(temperature);
  payload[2] = highByte(humidity);
  payload[3] = lowByte(humidity);

    modem.beginPacket();
    modem.write(payload, sizeof(payload));
    int err = modem.endPacket(true);
    if (err > 0) {
      Serial.println("Message sent correctly!");
    } else {
      Serial.println("Error sending message");
    }

  debugSerial.print("Temperature: ");
  debugSerial.println(temperature);
  debugSerial.print("Humidity: ");
  debugSerial.println(humidity);

  delay(900000);
}