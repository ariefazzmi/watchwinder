#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "setup.h"
#include <PNGdec.h>
#include "logo.h" // Image is stored here in an 8 bit array

PNG png; // PNG decoder inatance

#include "SPI.h"
#include "TFT_eSPI.h"

TFT_eSPI myGLCD = TFT_eSPI();

void TFT_autoUpdate(String s1, String s2, String d1, String d2, int m1, int m2){
  String D1;
  if(d1=="Clockwise"){
    D1="CW";
  } else if(d1=="Counter Clockwise"){
    D1="CCW";
  } else{
    D1="BOTH";
  }

  String D2;
  if(d2=="Clockwise"){
    D2="CW";
  } else if(d2=="Counter Clockwise"){
    D2="CCW";
  } else{
    D2="BOTH";
  }
  
  myGLCD.drawRect(7, 55, 110, 60, TFT_BLACK);
  myGLCD.drawRect(125, 55, 108, 60, TFT_BLACK);
  myGLCD.drawRect(7, 125, 110, 60, TFT_BLACK);
  myGLCD.drawRect(125, 125, 108, 60, TFT_BLACK);

  myGLCD.fillRect(9, 78, 222, 45,TFT_BLACK);
  myGLCD.fillRect(9, 148, 222, 45,TFT_BLACK);
  
  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.drawCentreString(s1, 60, 85, 1);
  myGLCD.drawCentreString(s2, 180, 85, 1);
  myGLCD.drawCentreString(D1, 60, 155, 1);
  myGLCD.drawCentreString(D2, 180, 155, 1);
  
  if(m1){
    myGLCD.fillRect(7, 195, 110, 40, TFT_DARKGREEN);
    myGLCD.drawCentreString("ON", 63, 205, 1);
  } else{
    myGLCD.fillRect(7, 195, 110, 40, TFT_RED);
    myGLCD.drawCentreString("OFF", 63, 205, 1);
  }
  
  if(m2){
    myGLCD.fillRect(125, 195, 108, 40, TFT_DARKGREEN);
    myGLCD.drawCentreString("ON", 180, 205, 1);
  } else{
    myGLCD.fillRect(125, 195, 108, 40, TFT_RED);
    myGLCD.drawCentreString("OFF", 180, 205, 1);
  }
}

void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[240];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  myGLCD.pushImage(0, 0 + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void boot_init(){
  myGLCD.fillScreen(0x000000);
  vTaskDelay(1000);
  int16_t rc = png.openFLASH((uint8_t *)logo, sizeof(logo), pngDraw);
  if (rc == PNG_SUCCESS) {
    myGLCD.startWrite();
    rc = png.decode(NULL, 0);
    myGLCD.endWrite();
  }
}

void TFT_printInit() {
  myGLCD.fillScreen(0x000000);
  myGLCD.drawRect(0, 0, 240, 240, TFT_WHITE);
  
  myGLCD.fillRect(7, 5, 110, 40, TFT_WHITE);
  myGLCD.fillRect(125, 5, 108, 40, TFT_WHITE);

  myGLCD.setTextColor(TFT_BLACK);
  myGLCD.setTextSize(3);
  myGLCD.drawCentreString("LEFT", 60, 15, 1);
  myGLCD.drawCentreString("RIGHT", 180, 15, 1);
  
  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.setTextSize(2);
  myGLCD.drawCentreString("TPD", 60, 64, 1);
  myGLCD.drawCentreString("TPD", 180, 64, 1);

  myGLCD.setTextSize(3);
  myGLCD.drawCentreString("VALUE", 60, 85, 1);
  myGLCD.drawCentreString("VALUE", 180, 85, 1);
  
  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.setTextSize(2);
  myGLCD.drawCentreString("DIR", 60, 134, 1);
  myGLCD.drawCentreString("DIR", 180, 134, 1);
  
  myGLCD.setTextSize(3);
  myGLCD.drawCentreString("VALUE", 60, 155, 1);
  myGLCD.drawCentreString("VALUE", 180, 155, 1);
  
  myGLCD.fillRect(7, 195, 110, 40, TFT_RED);
  myGLCD.fillRect(125, 195, 108, 40, TFT_DARKGREEN);

  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.drawCentreString("OFF", 60, 205, 1);

  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.drawCentreString("ON", 180, 205, 1);
}

void TFT_init(){
  myGLCD.init();
  myGLCD.setRotation(1);
  boot_init();
  
  TFT_printInit();
}

void TFT_Manual_Init(){
  myGLCD.drawRect(7, 55, 110, 60, TFT_WHITE);
  myGLCD.drawRect(125, 55, 108, 60, TFT_WHITE);
  myGLCD.drawRect(7, 125, 110, 60, TFT_WHITE);
  myGLCD.drawRect(125, 125, 108, 60, TFT_WHITE);
}

void TFT_switchUpdate(int side,int sw){
  if(side==1){
    if(sw==1){    
      myGLCD.fillRect(7, 195, 110, 40, TFT_DARKGREEN);
      myGLCD.drawCentreString("ON", 63, 205, 1);
    } else {
      myGLCD.fillRect(7, 195, 110, 40, TFT_RED);
      myGLCD.drawCentreString("OFF", 63, 205, 1);
    }
  } else{
    if(sw==1){
      myGLCD.fillRect(125, 195, 108, 40, TFT_DARKGREEN);
      myGLCD.drawCentreString("ON", 180, 205, 1);
    } else{
      myGLCD.fillRect(125, 195, 108, 40, TFT_RED);
      myGLCD.drawCentreString("OFF", 180, 205, 1);
    }
  }
}

void TFT_manualUpdate(String val, int cond){
  if(val=="Clockwise"){
    val="CW";
  } else if(val=="Counter Clockwise"){
    val="CCW";
  } else if(val=="Bidirectional"){
    val="BOTH";
  } else{
    val=val;
  }
  
  switch (cond){
    case 1 :
      myGLCD.drawRect(7, 55, 110, 60, TFT_WHITE);

      if(val!="")myGLCD.fillRect(9, 85, 106, 29, TFT_BLACK);
      myGLCD.setTextColor(TFT_WHITE);
      myGLCD.setTextSize(3);
      myGLCD.drawCentreString(val, 60, 85, 1);
      break;
    case 2 :
      myGLCD.drawRect(7, 55, 110, 60, TFT_BLACK);
      myGLCD.drawRect(125, 55, 108, 60, TFT_WHITE);

      if(val!="")myGLCD.fillRect(127, 85, 104, 29, TFT_BLACK);
      myGLCD.setTextColor(TFT_WHITE);
      myGLCD.setTextSize(3);
      myGLCD.drawCentreString(val, 180, 85, 1);
      break;
    case 3 :
      myGLCD.drawRect(125, 55, 108, 60, TFT_BLACK);
      myGLCD.drawRect(7, 125, 110, 60, TFT_WHITE);
      
      if(val!="")myGLCD.fillRect(9, 155, 106, 29, TFT_BLACK);
      myGLCD.setTextColor(TFT_WHITE);
      myGLCD.setTextSize(3);
      myGLCD.drawCentreString(val, 60, 155, 1);
      break;
    case 4 :
      myGLCD.drawRect(7, 125, 110, 60, TFT_BLACK);
      myGLCD.drawRect(125, 125, 108, 60, TFT_WHITE);

      if(val!="")myGLCD.fillRect(127, 155, 104, 29, TFT_BLACK);
      myGLCD.setTextColor(TFT_WHITE);
      myGLCD.setTextSize(3);
      myGLCD.drawCentreString(val, 180, 155, 1);
      break;
    case 5 :
      myGLCD.drawRect(125, 125, 108, 60, TFT_BLACK);
      break;
  }
}
#endif
