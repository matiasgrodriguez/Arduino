
#ifndef __PushButton_h__
#define __PushButton_h__

#include <WProgram.h>

#include "base.h"

class PushButton {
  
  uint8_t pin;
  bool wasDown;
  uint32_t lastUpTime;

public:

  PushButton(uint8_t pin) {
    this->pin = pin;
    wasDown = false;
    lastUpTime = 0;
  }
  
  void init() {
    pinMode( pin, INPUT );
    digitalWrite( pin, HIGH ); // http://sheepdogguides.com/arduino/aht0bounce1.htm
  }
  
  void tick(Clock *clock) {
    uint32_t currentTime = clock->currentTime();
    if( wasDown ) {
      if( isUp() && upElapsedTime( currentTime ) > 500L  ) {
        wasDown = false;
        lastUpTime = currentTime;
      }
    }
    
    /*if( wasDown && isUp() ) {
      wasDown = false;
    }*/
  }
  
  bool isUp() {
    return !isDown();
  }

  bool isDown() {
    return digitalRead( pin );
  }
  
  bool wasPushed() {
    if( !wasDown ) {
      if( isDown() ) {
        wasDown = true;
      }
      return wasDown;
    }
    return false;
  }
  
private:

  uint32_t upElapsedTime(uint32_t currentTime) {
    return currentTime - lastUpTime;
  }

};

#endif

