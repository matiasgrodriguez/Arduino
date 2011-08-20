
#ifndef __SimpleDelayTimeControl_h__
#define __SimpleDelayTimeControl_h__

#include "TimeControlBase.h"

class SimpleDelayTimeControl : public TimeControlBase {
  
  uint32_t delay;
  
public:

  SimpleDelayTimeControl(uint32_t playersTime, uint32_t delay) : TimeControlBase( playersTime, playersTime ) {
    this->delay = delay;
  }
  
  virtual ~SimpleDelayTimeControl() {
  }
  
  /*
   This time control is not supported by the game clock and TimeTracker. This time control works lie this:
    - At the beginning of the play the clock should wait for the delay period.
    - If the user makes a play before the delay the players keeps his original time.
    - I the player makes a play after the delay, he retains the consumed time after the delay.
  */
  
  
private:
  
};

#endif

