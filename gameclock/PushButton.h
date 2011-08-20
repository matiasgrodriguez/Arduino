
#ifndef __PushButton_h__
#define __PushButton_h__

#include <WProgram.h>

#include "base.h"

class PushButton {
  
  uint8_t pin;
  bool wasDown;

public:

  PushButton(uint8_t pin) {
    this->pin = pin;
    wasDown = false;
  }
  
  void tick(Clock *clock) {
    if( wasDown && isUp() ) {
      wasDown = false;
    }
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
  
};

#endif

