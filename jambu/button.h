#ifndef BUTTON_H
#define BUTTON_H

#include "setup.h"

int mainMenu=0;

bool button_check(int b){
  if(!digitalRead(b)){
    delay(75);
    if(!digitalRead(b)){
      return true;
    }
  }
  return false;
}

void P2(void *pvParameters){
  while(1){
    if(button_check(BUTTON2)){
      if(cond){
        mainMenu++;
        cond=false;
        TFT_manualUpdate("",mainMenu);
      }
    }
    vTaskDelay(10);
  }
}

void P1(void *pvParameters){
  while(1){
    if(cond){
      if(button_check(BUTTON1)){
        switch1=!switch1;
        flag1 = true;
        TFT_switchUpdate(1, switch1);
      }
    }
    vTaskDelay(10);
  }
}

void P3(void *pvParameters){
  while(1){
    if(cond){
      if(button_check(BUTTON3)){
        switch2=!switch2;
        flag2 = true;
        TFT_switchUpdate(2, switch2);
      }
    }
    vTaskDelay(10);
  }
}

void button_init(){
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
}

void set_menu(){
  if(button_check(BUTTON2)){
    mainMenu++;
    Serial.println("Menu = "+String(mainMenu));
    if(mainMenu>5){
      mainMenu=0;
      
    }
    TFT_manualUpdate("",mainMenu);
  }
  
  for(int i=0;i<3;i++){
    switch (mainMenu){
      case 1 :
        if(tpd1dump==tpd[i]){
          list = i;
          
          if(button_check(BUTTON3)){
            i++;
            if(i>2)i=0;
          }
          if(button_check(BUTTON1)){
            i--;
            if(i<0)i=2;
          }
          if(list!=i){
            Serial.println("TPD 1 Changed to > "+String(tpd[i]));
            tpd1dump = tpd[i];
            TFT_manualUpdate(tpd1dump,mainMenu);
          }
        }
        break;

      case 2 :
        if(tpd2dump==tpd[i]){
          list = i;
          
          if(button_check(BUTTON3)){
            i++;
            if(i>2)i=0;
          }
          if(button_check(BUTTON1)){
            i--;
            if(i<0)i=2;
          }
          if(list!=i){
            Serial.println("TPD 2 Changed to > "+String(tpd[i]));
            tpd2dump = tpd[i];
            TFT_manualUpdate(tpd2dump,mainMenu);
          }
        }
        break;

      case 3 :
        if(dir1dump==dir[i]){
          list = i;
          
          if(button_check(BUTTON3)){
            i++;
            if(i>2)i=0;
          }
          if(button_check(BUTTON1)){
            i--;
            if(i<0)i=2;
          }
          if(list!=i){
            Serial.println("DIR 1 Changed to > "+String(dir[i]));
            dir1dump = dir[i];
            TFT_manualUpdate(dir1dump,mainMenu);
          }
        }
        break;

      case 4 :
        if(dir2dump==dir[i]){
          list = i;
          
          if(button_check(BUTTON3)){
            vTaskDelay(100);
            i++;
            if(i>2)i=0;
          }
          if(button_check(BUTTON1)){
            i--;
            if(i<0)i=2;
          }
          if(list!=i){
            Serial.println("DIR 2 Changed to > "+String(dir[i]));
            dir2dump = dir[i];
            TFT_manualUpdate(dir2dump,mainMenu);
          }
        }
        break;

      case 5 :
        TFT_manualUpdate("",mainMenu);
        tpd1 = tpd1dump; mode1 = dir1dump;
        tpd2 = tpd2dump; mode2 = dir2dump;
        updateFirebase();
        Serial.println("RETURN TO MAIN LOOP");
        cond=!cond;
        mainMenu=0;
        break;
    }
  }
  interrupts();
}

#endif
