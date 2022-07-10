#ifndef BUTTON_H
#define BUTTON_H

#include "setup.h"

int mainMenu=0;

void IRAM_ATTR P2(){
  if(mainMenu==0)cond=!cond;
  if(cond==false)mainMenu++;
  if(mainMenu>5)mainMenu=0;
  TFT_manualUpdate("",mainMenu);
}

void IRAM_ATTR P1(){
  if(!flag1){
    flag1=true;
    switch1=!switch1;
  }
}

void IRAM_ATTR P3(){
  if(!flag2){
    flag2=true;
    switch2=!switch2;
  }
}

void button_init(){
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  attachInterrupt(BUTTON2, P2, RISING);
  attachInterrupt(BUTTON1, P1, RISING);
  attachInterrupt(BUTTON3, P3, RISING);
}

void set_menu(){
  noInterrupts();
  Serial.println(mainMenu);
  for(int i=0;i<3;i++){
    switch (mainMenu){
      case 1 :
        if(tpd1dump==tpd[i]){
          list = i;
          
          if(!digitalRead(BUTTON3)){
            vTaskDelay(100);
            i++;
            if(i>2)i=0;
          }
          if(!digitalRead(BUTTON1)){
            vTaskDelay(100);
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
          
          if(!digitalRead(BUTTON3)){
            vTaskDelay(100);
            i++;
            if(i>2)i=0;
          }
          if(!digitalRead(BUTTON1)){
            vTaskDelay(100);
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
          
          if(!digitalRead(BUTTON3)){
            vTaskDelay(100);
            i++;
            if(i>2)i=0;
          }
          if(!digitalRead(BUTTON1)){
            vTaskDelay(100);
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
          
          if(!digitalRead(BUTTON3)){
            vTaskDelay(100);
            i++;
            if(i>2)i=0;
          }
          if(!digitalRead(BUTTON1)){
            vTaskDelay(100);
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
