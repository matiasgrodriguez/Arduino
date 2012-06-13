
#ifndef __ArduinoClock_h__
#define __ArduinoClock_h__

#include <Arduino.h>

#include "Clock.h"

class ArduinoClock : public Clock {
  
public:
  
  virtual uint32_t currentTime() {
    return millis();
  }
  
};

#endif

