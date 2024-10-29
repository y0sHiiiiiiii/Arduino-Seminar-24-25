#include <Arduino.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>
#include <dht11.h>

#define RX_PIN 2
#define TX_PIN 3
#define BAUDRATE 9600
#define DHT11PIN 4
#define DATA_INTERVAL 3000  // Print data every 3 seconds (3000 milliseconds)

MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);
dht11 DHT11(DHT11PIN);

unsigned long getDataTimer = 0;

void setup() {
  Serial.begin(9600);

  mySerial.begin(BAUDRATE);
  myMHZ19.begin(mySerial);
  myMHZ19.autoCalibration();
}

void loop() {
  if (millis() - getDataTimer >= DATA_INTERVAL) {
    int CO2 = myMHZ19.getCO2();
    int8_t Temp = myMHZ19.getTemperature();
    int MicVolume = analogRead(0);
    int chk = DHT11.read();

    Serial.println();

    // Print CO2 and temperature (if MH-Z19 sensor is available and functioning)
    if (!isnan(CO2) && !isnan(Temp)) {
      Serial.print("CO2 (ppm): ");
      Serial.println(CO2);
      Serial.print("Temperature (C): ");
      Serial.println(Temp);
    } else {
      Serial.println("MH-Z19 sensor data unavailable");
    }

    // Print microphone volume
    Serial.print("Mic Volume: ");
    Serial.println(MicVolume);

    // Print humidity and temperature (if DHT11 sensor is available and functioning)
    if (chk == 0) {
      Serial.print("Humidity (%): ");
      Serial.println((float)DHT11.humidity, 2);
      Serial.print("Temperature (C): ");
      Serial.println((float)DHT11.temperature, 2);
    } else {
      Serial.println("DHT11 sensor error");
    }

    getDataTimer = millis();
  }
}