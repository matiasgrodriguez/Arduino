
#ifndef __Clock_h__
#define __Clock_h__

#include "base.h"

class Clock {

public:

  virtual uint32_t currentTime() = 0;
  virtual uint32_t currentTimeInMicros() = 0;
  
};

#endif

