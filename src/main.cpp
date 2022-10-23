#include <M5Stack.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "main.h"


// Data wire is plugged into port 33 on the ESP32
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

uint8_t state = 0;

void setup() {
  dacWrite(25, 0);
  // start serial port
  Serial.begin(115200);
  Serial.println("DS18B20 Test");

  M5.begin();
  M5.Lcd.sleep();
  M5.Lcd.setBrightness(0);

  // Start up the library
  sensors.begin();
  setCpuFrequencyMhz(10);
}

void loop() {
  M5.update();

  if(M5.BtnB.isPressed()) {
    state = 0;
    M5.Lcd.sleep();
    M5.Lcd.setBrightness(0);
  }
  else if(state == 1) leftBtnPushed();
  else if(M5.BtnA.isPressed()) {
    state = 1;
    M5.Lcd.wakeup();
    lcdSetup();
    leftBtnPushed();
  }

  delay(200);
}

void lcdSetup() {
  M5.Lcd.setBrightness(100);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(25, 220);
  M5.Lcd.printf("Open");
  M5.Lcd.setCursor(130, 220);
  M5.Lcd.printf("Close");
  M5.Lcd.setCursor(230, 220);
  M5.Lcd.printf("Auto");

  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Water Temp.");
  M5.Lcd.setCursor(150,  110);
  M5.Lcd.printf("dC");
}

void leftBtnPushed() {
  setCpuFrequencyMhz(240);
  char buf[6] = {0};
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  float waterTemp = sensors.getTempCByIndex(0);
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(waterTemp);

  (String(waterTemp, 2)).toCharArray(buf, sizeof(buf));
  M5.Lcd.setCursor(20, 110);
  M5.Lcd.printf(buf);

  setCpuFrequencyMhz(10);

  delay(2000);
}