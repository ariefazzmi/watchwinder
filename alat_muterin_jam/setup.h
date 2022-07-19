#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>

float hum;
float temp;

bool cond = true;
bool debugState = true;

int ls;
int winderTime = 10;

uint32_t lastCheck = 0;
#define checkInterval 5000

//=====================================================================================
const long timeOffset = 25200;
String dir[] = {"Clockwise", "Counter Clockwise", "Bidirectional"};
String tpd[] = {"650", "700", "800"};
String mode1;       String mode2;
String tpd1;        String tpd2;
int switch1;        int switch2;
float humDump;      float tempDump;
String tpd1dump;    String tpd2dump;
String dir1dump;    String dir2dump;
int sw1dump;        int sw2dump;
int rS1dump;        int rS2dump;

int runningStart1 = 0;
int runningStart2 = 0;

uint32_t lastSend = 0;
#define sendInterval 5000

#define FIREBASE_HOST "watchwinder-b194c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "eepjzNetlqeXUVyHkfp8dChz94w93ApKhAk6SF36"
#include "firebase.h"
//=====================================================================================

//=====================================================================================
#define TFT_GREY  0x7BEF
#define TOUCH_CS  4                     //bisa diganti -1 atau 4 biar ga keluar warning
#include "graphic.h"
//=====================================================================================

//=====================================================================================
// Generic Button & LED ====================================
#define BUTTON1      32
#define BUTTON2      23
#define BUTTON3      16

#include "button.h"
//=====================================================================================

//=====================================================================================
//Stepper Motor 1 & Stepper Motor 2 ========================
#define MotorR1      19
#define MotorR2      18
#define MotorR3      5
#define MotorR4      17

#define MotorL1      27
#define MotorL2      26
#define MotorL3      25
#define MotorL4      33

const int MotorInterfaceType = 8;

#include "motor.h"
//=====================================================================================

//=====================================================================================
#define BME280_ADDR 0x76
#define MCP9808_ADDR 0x18
#include "sensor.h"
//=====================================================================================

#endif
