#ifndef SENSOR_H
#define SENSOR_H

#include "setup.h"
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "Adafruit_MCP9808.h"

Adafruit_BME280 Hum;
Adafruit_MCP9808 Temp = Adafruit_MCP9808();

void MCP9808_init() {
  Temp.begin(MCP9808_ADDR);
  Temp.setResolution(3);
}

void BME280_init() {
  bool stat = Hum.begin(BME280_ADDR);
  if (!stat) {
    Serial.println("BME280 Error");
    while(1);
  }
  vTaskDelay(1000);
}

void MCP9808_readTemp(bool debug){
  Temp.wake();
  temp = Temp.readTempC() - tempCal;
  if(debug)Serial.println("Temperature : " + String(temp, 1));
}

void BME280_readHum(bool debug){
  hum = Hum.readHumidity() - humCal;
  if(debug)Serial.println("Humidity : " + String(hum));
}

#endif
