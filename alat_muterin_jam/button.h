#ifndef BUTTON_H
#define BUTTON_H

#include "setup.h"

int mainMenu=0;

void Button_init(){
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
}

void switchPressed(){
  if(mainMenu==0){
    if(!digitalRead(BUTTON1) && !digitalRead(BUTTON3)){
      ESP.restart();
    }
    
    if(!digitalRead(BUTTON1)){
      vTaskDelay(100);

      switch1=!switch1;
      runningStart1 = timeClient.getMinutes();;
      toggleSwitch(1, switch1, runningStart1);
      TFT_switchUpdate(1, switch1);

      Serial.println("Switch 1 changed");
    }
    
    if(!digitalRead(BUTTON3)){
      vTaskDelay(100);
      
      switch2=!switch2;
      runningStart2 = timeClient.getMinutes();
      toggleSwitch(2, switch2, runningStart2);
      TFT_switchUpdate(2, switch2);

      Serial.println("Switch 2 changed");
    }
  }
}

void buttonPressed(){
  if(mainMenu==0){
    if(!digitalRead(BUTTON1)&&!digitalRead(BUTTON3)){
      ESP.restart();
    }
    
    if(!digitalRead(BUTTON2)){
      vTaskDelay(100);
      Serial.println("PROCEED TO MENU!");
      cond=!cond;
      mainMenu++;
      TFT_manualUpdate("",mainMenu);
    }
  } else{
    if(!digitalRead(BUTTON2)){
      vTaskDelay(100);
      mainMenu++;
      TFT_manualUpdate("",mainMenu);
      Serial.println(mainMenu);
    }
    
    for(int i=0;i<3;i++){
      switch (mainMenu){
        case 1 :
          if(tpd1dump==tpd[i]){
            ls = i;
            
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
            if(ls!=i){
              Serial.println("TPD 1 Changed to > "+String(tpd[i]));
              tpd1dump = tpd[i];
              TFT_manualUpdate(tpd1dump,mainMenu);
            }
          }
          break;

        case 2 :
          if(tpd2dump==tpd[i]){
            ls = i;
            
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
            if(ls!=i){
              Serial.println("TPD 2 Changed to > "+String(tpd[i]));
              tpd2dump = tpd[i];
              TFT_manualUpdate(tpd2dump,mainMenu);
            }
          }
          break;

        case 3 :
          if(dir1dump==dir[i]){
            ls = i;
            
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
            if(ls!=i){
              Serial.println("DIR 1 Changed to > "+String(dir[i]));
              dir1dump = dir[i];
              TFT_manualUpdate(dir1dump,mainMenu);
            }
          }
          break;

        case 4 :
          if(dir2dump==dir[i]){
            ls = i;
            
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
            if(ls!=i){
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
  }
}

void switchClick(void *pvParameters){
  for (;;)
  {
    switchPressed();
    vTaskDelay(100);
  }
}

void buttonClick(void *pvParameters){
  for (;;)
  {
    buttonPressed();
    vTaskDelay(100);
  }
}

#endif
