#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SPI.h>
#include <M5Stack.h>


#define BMP_SCK G18
#define BMP_MISO G19
#define BMP_MOSI G23
#define BMP_CS G5

Adafruit_BMP280 bmp(BMP_CS);
unsigned long delayTime;
void printValues();

void setup() {
  /* シリアル初期化 */
  Serial.begin(9600);
  Serial.println("BMP280 Test");


  /* BME280初期化 */
  if (! bmp.begin()) {
     Serial.println("Could not find a valid BMP280 sensor, check wiring!");
     while (1);
  }

  Serial.println("-- Default Test --");
  Serial.println("normal mode, 16x oversampling for all, filter off,");
  Serial.println("0.5ms standby period");
  delayTime = 5000;
}

void loop() {
    printValues();
    delay(delayTime);
}

/* データ表示 */
void printValues() {
/* 温度表示 */
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

/* 気圧表示 */
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

/* 気圧表示 */
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" %");

/* 湿度表示 */
  // Serial.print("Humidity = ");
  // Serial.print(bmp.readHumidity());
  // Serial.println(" %");

  Serial.println();
}