#ifndef FIREBASE_H
#define FIREBASE_H

#include "setup.h"
#include <WiFiManager.h>
#include <FirebaseESP32.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

FirebaseData fb;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", timeOffset);

String ntp() {
  String tm = timeClient.getFormattedTime();
  return tm;
}

void WiFi_init(){
  WiFi.mode(WIFI_STA);
  WiFiManager wm;

//  wm.resetSettings();

  if(!wm.autoConnect()) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } 
  else {
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
  }
  
  Firebase.reconnectWiFi(true);

  Firebase.setReadTimeout(fb, 1000 * 60);
  Firebase.setwriteSizeLimit(fb, "small");
  Firebase.setFloatDigits(1);
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  timeClient.begin();
}

void DB_sendData(bool debug){
  if(debug){
    if(temp==0.00 && hum==0){  //Filter saat tidak ada data yang diterima              
      Firebase.setString(fb, "temp", "--");
      Firebase.setString(fb, "humi", "--");
    } else{
      if(temp!=0.00 && temp!=tempDump){  //Filter data BPM
        tempDump = temp;
        Firebase.setFloat(fb, "temp", temp);
        String path1 = "User/1/tempList/" + String(timeClient.getMonth()) + "-" + String(timeClient.getDate()) + " " + String(timeClient.getHours())+":"+String(timeClient.getMinutes())+":"+String(timeClient.getSeconds());
        Firebase.setFloat(fb, path1, temp);
      }
      if(hum!=0 && hum!=humDump){  //Filter data SPO2
        humDump = hum;
        Firebase.setInt(fb, "humi", hum);
        String path2 = "User/1/humiList/" + String(timeClient.getMonth()) + "-" + String(timeClient.getDate()) + " " + String(timeClient.getHours())+":"+String(timeClient.getMinutes())+":"+String(timeClient.getSeconds());
        Firebase.setInt(fb, path2, hum);
      }
    }
    Firebase.setString(fb, "time", ntp());
  }
}

bool DB_getData(bool debug){
  int flag = 0;
  Firebase.getString(fb, "Speed/0");
  tpd1 = fb.stringData();
  if(tpd1!=tpd1dump){
    tpd1dump=tpd1;
    flag++;
  }
  if(debug)Serial.println("TPD Left : " + String(tpd1));
  
  Firebase.getInt(fb, "Switch1");
  switch1 = fb.intData();
  if(switch1!=sw1dump){
    sw1dump=switch1;
    flag++;
  }
  if(debug)Serial.println("Switch Left : " + String(switch1));
  
  Firebase.getString(fb, "Rotation/0");
  mode1 = fb.stringData();
  if(mode1!=dir1dump){
    dir1dump=mode1;
    flag++;
  }
  if(debug)Serial.println("Arah Left : " + mode1);

  Firebase.getString(fb, "Speed2/0");
  tpd2 = fb.stringData();
  if(tpd2!=tpd2dump){
    tpd2dump=tpd2;
    flag++;
  }
  if(debug)Serial.println("TPD Right : " + String(tpd2));
  
  Firebase.getInt(fb, "Switch2");
  switch2 = fb.intData();
  if(switch2!=sw2dump){
    sw2dump=switch2;
    flag++;
  }
  if(debug)Serial.println("Switch Right : " + String(switch2));
  
  Firebase.getString(fb, "Rotation2/0");
  mode2 = fb.stringData();
  if(mode2!=dir2dump){
    dir2dump=mode2;
    flag++;
  }
  if(debug)Serial.println("Arah Right : " + mode2);

  Firebase.getInt(fb, "mnt1");
  runningStart1 = fb.intData();
  if(debug)Serial.println("Running Time : " + String(runningStart1));
  Firebase.getInt(fb, "mnt2");
  runningStart2 = fb.intData();
  if(debug)Serial.println("Running Time : " + String(runningStart2));
  
  if(flag>0){
    return true;
  } else{
    return false;
  }
}

void switchCheck(){
  if(flag1){
    Firebase.setInt(fb, "Switch1", switch1);
    Serial.println("Switch 1 updated!");
    runningStart1 = timeClient.getMinutes()+1;
    Firebase.setInt(fb, "mnt1",runningStart1);
    flag1 = false;
    TFT_switchUpdate(1, switch1);
  }

  if(flag2){
    Firebase.setInt(fb, "Switch2", switch2);
    Serial.println("Switch 2 updated!");
    runningStart2 = timeClient.getMinutes()+1;
    Firebase.setInt(fb, "mnt2",runningStart2);
    flag2 = false;
    TFT_switchUpdate(2, switch2);
  }    
}

void updateFirebase(){
  Firebase.setString(fb, "Speed/0", tpd1);
  Firebase.setString(fb, "Rotation/0", mode1);
  
  Firebase.setString(fb, "Speed2/0", tpd2);
  Firebase.setString(fb, "Rotation2/0", mode2);
}

#endif
