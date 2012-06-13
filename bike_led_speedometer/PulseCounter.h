
#ifndef __PulseCounter_h__
#define __PulseCounter_h__

#include "Clock.h"
#include "DigitalPin.h"

class PulseCounter {
  
  DigitalPin *pin;
  bool state;

public:

  PulseCounter(DigitalPin *pin) {
    this->pin = pin;
    state = false;
  }

  virtual void tick(Clock *clock) {
  }

};

#endif
