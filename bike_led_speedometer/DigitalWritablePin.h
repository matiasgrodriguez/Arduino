
#ifndef __DigitalWritablePin_h__
#define __DigitalWritablePin_h__

#include "DigitalPin.h"

class DigitalWritablePin : public DigitalPin {
  
public:

  virtual void set(bool val) = 0;
  virtual void toggle() = 0;
  
};

#endif
