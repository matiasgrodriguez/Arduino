
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
  
  
private:
  
};

#endif

