#include <Arduino.h>
#include "MHZ19.h"
#include <SoftwareSerial.h>
#include <dht11.h>
#include <SPI.h>
#include <SD.h>

// Pin-Definitionen
#define RX_PIN 2
#define TX_PIN 3
#define DHT11PIN 4
#define SD_CS_PIN 10

// RGB LED Pins
#define G_PIN 8
#define R_PIN 7
#define B_PIN 6

// MHZ19 CO2-Sensor
MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);

// DHT11 Temperatur- und Feuchtigkeitssensor
dht11 DHT11;

// Variablen
int MicVolume;
unsigned long getDataTimer = 0;
File dataFile;
int measurementNumber = 1; // Zähler für die Messungen

// Helper function to control the RGB LED
void setLEDColor(int red, int green, int blue) {
  analogWrite(R_PIN, red);
  analogWrite(G_PIN, green);
  analogWrite(B_PIN, blue);
}

void setup() {
  Serial.begin(9600);

  // Set RGB LED pins as output
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  
  // Start with green to indicate everything is working
  setLEDColor(0, 255, 0);  // Green

  // Initialisiere MHZ19 CO2-Sensor
  mySerial.begin(9600);
  myMHZ19.begin(mySerial);
  myMHZ19.autoCalibration();

  // Initialisiere SD-Karte
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD-Karten-Initialisierung fehlgeschlagen!");
    setLEDColor(255, 0, 0);  // Red (Error)
    while (1);
  }
  Serial.println("SD-Karte initialisiert.");
  
  getDataTimer = millis(); // Initialisiere getDataTimer in setup
}

void loop() {
  if (millis() - getDataTimer >= 5000) { // Prüfe alle 5 Sekunden

    // Set LED to orange while printing a measurement
    setLEDColor(255, 165, 0);  // Orange

    // Lese und drucke CO2-Konzentration vom MHZ19
    int CO2 = myMHZ19.getCO2();

    // Lese Mikrofonlautstärke (analoger Wert)
    MicVolume = analogRead(0);

    // Lese Feuchtigkeit und Temperatur vom DHT11
    int chk = DHT11.read(DHT11PIN);
    float humidity = (float)DHT11.humidity;
    float temperature = (float)DHT11.temperature;

    // Öffne oder erstelle die Datendatei zum Schreiben
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
      // Schreibe sowohl in die Konsole als auch in die Datei
      Serial.print(measurementNumber);
      Serial.println(". Messung:");
      dataFile.print(measurementNumber);
      dataFile.println(". Messung:");

      Serial.print("CO2: ");
      Serial.print(CO2);
      Serial.println(" ppm");
      dataFile.print("CO2: ");
      dataFile.print(CO2);
      dataFile.println(" ppm");

      Serial.print("Mikrofon: ");
      Serial.println(MicVolume);
      dataFile.print("Mikrofon: ");
      dataFile.println(MicVolume);

      Serial.print("Feuchtigkeit: ");
      Serial.print(humidity, 0);
      Serial.println(" %");
      dataFile.print("Feuchtigkeit: ");
      dataFile.print(humidity, 0);
      dataFile.println(" %");

      Serial.print("Temperatur: ");
      Serial.print(temperature, 0);
      Serial.println(" °C");
      dataFile.print("Temperatur: ");
      dataFile.print(temperature, 0);
      dataFile.println(" °C");

      // Leerzeile für Lesbarkeit
      Serial.println();
      dataFile.println();

      // Schließe die Datei
      dataFile.close();
    } else {
      Serial.println("Fehler beim Öffnen der Datei!");
      setLEDColor(255, 0, 0);  // Red (Error)
    }

    // Inkrementiere den Messungszähler
    measurementNumber++;

    // Set LED back to green after measurement is done
    setLEDColor(0, 255, 0);  // Green

    getDataTimer = millis(); // Timer zurücksetzen.
  }
}
