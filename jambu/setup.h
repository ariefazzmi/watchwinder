#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>

/*                              Global Variable                                      */
//=====================================================================================
int hum;
float temp;

float tempCal = 0.0;
int humCal = 1;

String mode1;       String mode2;
String tpd1;        String tpd2;
int switch1;        int switch2;

bool cond = true;
bool debugState = true;

int list;
int winderTime = 10;              //Specific calibration turn rotation time a day

uint32_t lastSend = 0;
#define checkSend 10000           //interval send data firebase

uint32_t lastGet = 0;
#define checkGet 5000             //interval get data firebase
//=====================================================================================

/*                                 LCD ST7789                                        */
//=====================================================================================
#define TFT_GREY  0x7BEF
#define TOUCH_CS
#include "graphic.h"
//=====================================================================================

/*                             Firebase Database                                     */
//=====================================================================================
const long timeOffset = 25200;
String dir[] = {"Clockwise", "Counter Clockwise", "Bidirectional"};
String tpd[] = {"650", "700", "800"};
float humDump;      float tempDump;
String tpd1dump;    String tpd2dump;
String dir1dump;    String dir2dump;
int sw1dump;        int sw2dump;
bool flag1 = false;         bool flag2 = false;
bool flagMenu = true;

int runningStart1 = 0;
int runningStart2 = 0;

int listCount = 0;

#define FIREBASE_HOST "watchwinder-b194c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "eepjzNetlqeXUVyHkfp8dChz94w93ApKhAk6SF36"
#include "firebase.h"
//=====================================================================================

/*                                    Button                                         */
//=====================================================================================
#define BUTTON1      32
#define BUTTON2      23
#define BUTTON3      16

#include "button.h"
//=====================================================================================

/*                                 Motor Driver                                      */
//=====================================================================================
//Stepper Motor 1 & Stepper Motor 2 ========================
#define MotorR1      27
#define MotorR2      26
#define MotorR3      25
#define MotorR4      33

#define MotorL1      19
#define MotorL2      18
#define MotorL3      5
#define MotorL4      17

const int MotorInterfaceType = 8;

#include "motor.h"
//=====================================================================================

/*                          Temperature & Humidity Sensor                            */
//=====================================================================================
#define BME280_ADDR 0x76
#define MCP9808_ADDR 0x18
#include "sensor.h"
//=====================================================================================

/*                                    RGB LED                                        */
//=====================================================================================
#define LED_PIN     4
#define NUM_LEDS    8
#define BRIGHTNESS  8
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#include "init.h"
//=====================================================================================
#endif
