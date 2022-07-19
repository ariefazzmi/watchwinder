#ifndef INIT_H
#define INIT_H

#include "setup.h"
#include <SPI.h>
#define FASTLED_ALL_PINS_HARDWARE_SPI

#include <FastLED.h>

CRGB leds[NUM_LEDS];

void setup_begin(){
  myGLCD.begin();
  vTaskDelay(1000);
  myGLCD.fillScreen(TFT_BLACK);
  vTaskDelay(200);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  for(int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB::White;
  }
  FastLED.show();

  myGLCD.setRotation(1);
  boot_init();
  vTaskDelay(2000);
  myGLCD.fillScreen(TFT_BLACK);
  vTaskDelay(200);
  
  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.setTextSize(2);
  myGLCD.drawString("Preparing...", 1, 1);
  Serial.begin(115200);
  vTaskDelay(250);
  myGLCD.drawString("Wi-Fi Set", 1, 20);
  vTaskDelay(250);
  WiFi_init();
  DB_getData(debugState);
  myGLCD.drawString("Connected!", 1, 39);
  vTaskDelay(250);
  myGLCD.drawString("Sensor Init", 1, 58);
  vTaskDelay(250);
  BME280_init();
  MCP9808_init();
  myGLCD.drawString("Detected!", 1, 77);
  vTaskDelay(250);
  myGLCD.drawString("Attach Motor", 1, 96);
  Motor_init();
  vTaskDelay(250);
  myGLCD.drawString("Installed!", 1, 115);
  vTaskDelay(250);
  myGLCD.drawString("Config Button", 1, 134);
  button_init();
  vTaskDelay(250);
  myGLCD.drawString("Set-up motor", 1, 153);
//  xTaskCreate(runMotor1, "Motor 1 Running", 10000, NULL, tskIDLE_PRIORITY, NULL);
//  xTaskCreate(runMotor2, "Motor 2 Running", 10000, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(P1, "Button 1 Press", 1024, NULL, 1, NULL);
  xTaskCreate(P2, "Button 2 Press", 1024, NULL, 1, NULL);
  xTaskCreate(P3, "Button 3 Press", 1024, NULL, 1, NULL);
  vTaskDelay(250);
  myGLCD.drawString("Device Ready!", 1, 210);
  vTaskDelay(3000);
  TFT_printInit();
  TFT_autoUpdate(tpd1, tpd2, mode1, mode2, switch1, switch2);
}

#endif
