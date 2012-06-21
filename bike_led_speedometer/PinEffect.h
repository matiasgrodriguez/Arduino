
#ifndef __PinEffect_h__
#define __PinEffect_h__

#include "Clock.h"
#include "DigitalWritablePin.h"

class PinEffect {
  
public:
  virtual void tick(Clock *clock) = 0;
  virtual void apply(DigitalWritablePin *pin) = 0;
  
};

#endif


