#include <M5Stack.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 33 on the ESP32
#define ONE_WIRE_BUS 33

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void printValues();

void setup() {

  // start serial port
  Serial.begin(115200);
  Serial.println("DS18B20 Test");

  // Start up the library
  sensors.begin();
}

void loop() {
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));

  delay(5000);
}
