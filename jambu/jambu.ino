#include "setup.h"

void setup() {
  setup_begin();
}

void loop() {
  timeClient.update();
  switchCheck();
  
  runMotor1();
  runMotor2();
  
  if(cond){
    if(millis() - lastSend > checkSend){
      for(int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB::Blue;
      }
      FastLED.show();
      BME280_readHum(debugState);
      MCP9808_readTemp(debugState);
      DB_sendData(debugState);
      lastSend = millis();
    }

    if(millis() - lastGet > checkGet){
      for(int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB::White;
      }
      FastLED.show();
      DB_getData(debugState);
      if(cond)TFT_autoUpdate(tpd1, tpd2, mode1, mode2, switch1, switch2);
      lastGet = millis();
    }
  } else{
    if(mainMenu!=0){
      for(int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB::Red;
      }
      FastLED.show();
      do{
        set_menu();
      } while(mainMenu!=0);
    }
  }
}
