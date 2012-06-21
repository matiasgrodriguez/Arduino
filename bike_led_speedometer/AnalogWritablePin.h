
#ifndef __AnalogWritablePin_h__
#define __AnalogWritablePin_h__

#include "base.h"

class AnalogWritablePin {
  
public:

  virtual void set(uint8_t value) = 0;
  
};

#endif

