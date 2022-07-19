#ifndef MOTOR_H
#define MOTOR_H

#include "setup.h"
#include <AccelStepper.h>

AccelStepper LeftMotor = AccelStepper(MotorInterfaceType, MotorL1, MotorL3, MotorL2, MotorL4);
AccelStepper RightMotor = AccelStepper(MotorInterfaceType, MotorR1, MotorR3, MotorR2, MotorR4);

void Motor_init(){
  LeftMotor.setMaxSpeed(1000);
  RightMotor.setMaxSpeed(1000);
}

void run_motor(int motorSide, int motorState, int turn, int pos, String rot, bool debug){
  if(motorState==1){
    if(turn == 800){
      pos*=33;
      pos+=682;
      if(timeClient.getHours()==winderTime){
        pos+=16;
      }
    } else if(turn == 700){
      pos*=29;
      pos+=341;
      if(timeClient.getHours()==winderTime){
        pos+=8;
      }
    } else{
      pos*=27;
      pos+=170;
      if(timeClient.getHours()==winderTime){
        pos+=16;
      }
    }

    if(motorSide==1  && timeClient.getMinutes()==runningStart1){
      LeftMotor.setCurrentPosition(0);
      if(rot=="Counter Clockwise"){
        while (LeftMotor.currentPosition() != -pos) {
          LeftMotor.setSpeed(-1000);
          LeftMotor.runSpeed();
          if(debug)Serial.println(LeftMotor.currentPosition());
        }
      } else if(rot=="Clockwise"){
        while (LeftMotor.currentPosition() != pos) {
          LeftMotor.setSpeed(1000);
          LeftMotor.runSpeed();
          if(debug)Serial.println(LeftMotor.currentPosition());
        }
      } else{
        while (LeftMotor.currentPosition() != pos/2) {
          LeftMotor.setSpeed(1000);
          LeftMotor.runSpeed();
          if(debug)Serial.println(LeftMotor.currentPosition());
        }
        while (LeftMotor.currentPosition() != 0) {
          LeftMotor.setSpeed(-1000);
          LeftMotor.runSpeed();
          if(debug)Serial.println(LeftMotor.currentPosition());
        }
      }    
    } else if(motorSide==2 && timeClient.getMinutes()==runningStart2){
      RightMotor.setCurrentPosition(0);
      if(rot=="Counter Clockwise"){
        while (RightMotor.currentPosition() != -pos) {
          RightMotor.setSpeed(-1000);
          RightMotor.runSpeed();
          if(debug)Serial.println(RightMotor.currentPosition());
        }
      } else if(rot=="Clockwise"){
        while (RightMotor.currentPosition() != pos) {
          RightMotor.setSpeed(1000);
          RightMotor.runSpeed();
          if(debug)Serial.println(RightMotor.currentPosition());
        }
      } else{
        while (RightMotor.currentPosition() != pos/2) {
          RightMotor.setSpeed(1000);
          RightMotor.runSpeed();
          if(debug)Serial.println(RightMotor.currentPosition());
        }
        while (RightMotor.currentPosition() != 0) {
          RightMotor.setSpeed(-1000);
          RightMotor.runSpeed();
          if(debug)Serial.println(RightMotor.currentPosition());
        }
      }
    }
    TFT_autoUpdate(tpd1, tpd2, mode1, mode2, switch1, switch2);
  }
}

#endif
