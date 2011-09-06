
#ifndef __UiHandler_h__
#define __UiHandler_h__

#include "Buzzer.h"
#include "GameClock.h"

extern Buzzer buzzer;

class UiHandler {

public:

  virtual void tick(Clock *clock) = 0;
  virtual void render(Clock *clock) = 0;
  
protected:

  virtual void beep() {
    buzzer.beepFor( 150 );
  }
  
};

#endif

