#include <Arduino.h>

#define BUTTON1 32
#define BUTTON2 23
#define BUTTON3 16

int button1State = 0;
int button2State = 0;
int button3State = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
}

void loop() {
  button1State = digitalRead(BUTTON1);
  button2State = digitalRead(BUTTON2);
  button3State = digitalRead(BUTTON3);

  if (button1State == LOW){
    Serial.println("Button 1 is pressed.");
  }  
  else if (button2State == LOW){
    Serial.println("Button 2 is pressed.");
  }
  else if (button3State == LOW){
    Serial.println("Button 3 is pressed.");
  }
  else{
    Serial.println("No button detected.");
  }
  delay(2000);
}
