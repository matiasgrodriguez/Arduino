
#ifndef __UiHandler_h__
#define __UiHandler_h__

#include "GameClock.h"

class UiHandler {

public:

  virtual void tick(Clock *clock) = 0;
  virtual void render(Clock *clock) = 0;
  
};

#endif

