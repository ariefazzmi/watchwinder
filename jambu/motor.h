#ifndef MOTOR_H
#define MOTOR_H

#include "setup.h"
#include <AccelStepper.h>

AccelStepper LeftMotor = AccelStepper(MotorInterfaceType, MotorL1, MotorL3, MotorL2, MotorL4);
AccelStepper RightMotor = AccelStepper(MotorInterfaceType, MotorR1, MotorR3, MotorR2, MotorR4);

int pos = 4096;
int speed_ = 1000;

void Motor_init(){
  LeftMotor.setMaxSpeed(1000);
  RightMotor.setMaxSpeed(1000);
}

void runMotor1(){
  if(switch1==1){
    int pos1=0;
    if(tpd1 == "800"){
      pos1=pos*33;
      pos1+=1534;
      if(timeClient.getHours()==winderTime){
        pos1+=48;
      }
    } else if(tpd1 == "700"){
      pos1=pos*29;
      pos1+=909;
      if(timeClient.getHours()==winderTime){
        pos1+=28;
      }
    } else{
      pos1=pos*27;
      pos1+=453;
      if(timeClient.getHours()==winderTime){
        pos1+=51;
      }
    }
    
    if(timeClient.getMinutes()==runningStart1){
      cond = false;
      RightMotor.setCurrentPosition(0);
      if(mode1=="Counter Clockwise"){
        while (RightMotor.currentPosition() != -pos1) {
          RightMotor.setSpeed(-speed_);
          RightMotor.runSpeed();
        }
      } else if(mode1=="Clockwise"){
        while (RightMotor.currentPosition() != pos1) {
          RightMotor.setSpeed(speed_);
          RightMotor.runSpeed();
        }
      } else{
        while (RightMotor.currentPosition() != pos1/2) {
          RightMotor.setSpeed(speed_);
          RightMotor.runSpeed();
        }
        while (RightMotor.currentPosition() != 0) {
          RightMotor.setSpeed(-speed_);
          RightMotor.runSpeed();
        }
      }
      cond = true;
    }
  }
}

void runMotor2(){
  if(switch2==1){
    int pos2=0;
    if(tpd2 == "800"){
      pos2=pos*33;
      pos2+=1534;
      if(timeClient.getHours()==winderTime){
        pos2+=48;
      }
    } else if(tpd2 == "700"){
      pos2=pos*29;
      pos2+=909;
      if(timeClient.getHours()==winderTime){
        pos2+=28;
      }
    } else{
      pos2=pos*27;
      pos2+=453;
      if(timeClient.getHours()==winderTime){
        pos2+=51;
      }
    }
    
    if(switch1==1 && runningStart1==runningStart2){
      runningStart2+=3;
    }
    
    if(timeClient.getMinutes()==runningStart2){
      cond = false;
      LeftMotor.setCurrentPosition(0);
      if(mode2=="Counter Clockwise"){
        while (LeftMotor.currentPosition() != -pos2) {
          LeftMotor.setSpeed(-speed_);
          LeftMotor.runSpeed();
        }
      } else if(mode2=="Clockwise"){
        while (LeftMotor.currentPosition() != pos2) {
          LeftMotor.setSpeed(speed_);
          LeftMotor.runSpeed();
        }
      } else{
        while (LeftMotor.currentPosition() != pos2/2) {
          LeftMotor.setSpeed(speed_);
          LeftMotor.runSpeed();
        }
        while (LeftMotor.currentPosition() != 0) {
          LeftMotor.setSpeed(-speed_);
          LeftMotor.runSpeed();
        }
      }
      cond = true;
    }
  }
}

#endif
