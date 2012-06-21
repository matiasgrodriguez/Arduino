
#ifndef __PinEffect_h__
#define __PinEffect_h__

#include "PinEffect.h"

class FxFade : public PinEffect{
  
public: 

  virtual void tick(Clock *clock) {
  }
  
  virtual void apply(DigitalWritablePin *pin) {
  }
  
};

#endif
