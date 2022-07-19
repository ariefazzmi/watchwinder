#include "setup.h"

void setup() {
  Serial.begin(115200);
  WiFi_init();
  BME280_init();
  MCP9808_init();
  TFT_init();
  Motor_init();
  Button_init();
  xTaskCreate(buttonClick, "Button", 4096, NULL, 1, NULL);
  xTaskCreate(switchClick, "Switch", 4096, NULL, 1, NULL);
}

void loop() {
  timeClient.update();
  if (cond) {
    BME280_readHum(debugState);
    MCP9808_readTemp(debugState);
    DB_sendData(debugState);
    if(DB_getData(debugState)){
      if(cond)TFT_autoUpdate(tpd1, tpd2, mode1, mode2, switch1, switch2);
    }
    vTaskDelay(5000);
  }
  if (millis() - lastCheck > checkInterval) {
    run_motor(1, switch1, tpd1.toInt(), 2048, mode1, !debugState);
    run_motor(2, switch2, tpd2.toInt(), 2048, mode2, !debugState);
    lastCheck = millis();
  }
}
