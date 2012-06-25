
#ifndef __ArduinoClock_h__
#define __ArduinoClock_h__

#include <Arduino.h>

#include "Clock.h"

class ArduinoClock : public Clock {
  
  uint32_t currentTimeMillis;
  
public:

  virtual void update() {
    currentTimeMillis = millis();
  }
  
  virtual uint32_t currentTime() {
    return currentTimeMillis;
  }

  virtual uint32_t currentTimeInMicros() {
    return micros();
  }
  
};

#endif

