
#ifndef __PulseCounter_h__
#define __PulseCounter_h__

#include "Clock.h"
#include "DigitalPin.h"

class PulseCounter {
  
  DigitalPin *pin;
  uint32_t count;
  bool state;

public:

  PulseCounter(DigitalPin *pin) {
    this->pin = pin;
    count = 0;
    state = false;
  }

  virtual void tick(Clock *clock) {
    bool pinState = pin->isSet();
    if( state == pinState ) {
      return; //no state change
    }
    //state changed
    state = pinState;
    if( state ) {
      count++;
    }
  }
  
  uint32_t pulsesPerSecond() {
    return count;
  }

};

#endif
