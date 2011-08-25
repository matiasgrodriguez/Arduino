
#ifndef __UiHandler_h__
#define __UiHandler_h__

#include "Clock.h"

class UiHandler {

public:

  virtual void tick(Clock *clock) = 0;
  virtual void render() = 0;
  
};

#endif

