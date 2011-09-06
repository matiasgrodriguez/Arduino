
#ifndef __Buzzer_h__
#define __Buzzer_h__

#include <WProgram.h>

class Buzzer{
  
  int port;
  long expirationTime;
  long toneDuration;
  long toneExpirationTimeUs;
  boolean isBuzzing;
  
  public:
  Buzzer(int aPort){
    port = aPort;
    expirationTime = 0;
    toneExpirationTimeUs = 0;
    toneDuration = 1;
    isBuzzing = false;
    initPort();
  }
  
  void beepFor(int milliseconds){
    expirationTime = millis() + milliseconds;
    startBuzzing();
  }
  
  void playTone(long frequencyInHz, int milliseconds) {
    long oneSecondInUs = 1000000;
    toneDuration = (oneSecondInUs/frequencyInHz) / 2;
    resetToneExpirationTime();
    beepFor(milliseconds);
  }
  
  
  void tick(){
    if (millis() > expirationTime){
      stopBuzzing();
      return;
    }

    if (micros() > toneExpirationTimeUs){
       if (isBuzzing)
         stopBuzzing();
       else
         startBuzzing();
       
       resetToneExpirationTime();
     }
     
  }

  void stopBuzzing() {
    digitalWrite(port, LOW);
    isBuzzing = false;
  }

private:

  void resetToneExpirationTime(){
    toneExpirationTimeUs = micros() + toneDuration;
  }

  void initPort() {
    pinMode(port, OUTPUT);
  }
  
  void startBuzzing() {
    digitalWrite(port, HIGH);
    isBuzzing = true;
  }
  
};

#endif __Buzzer_h__

