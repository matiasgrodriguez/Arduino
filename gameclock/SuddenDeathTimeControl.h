
#ifndef __SuddenDeathTimeControl_h__
#define __SuddenDeathTimeControl_h__

#include "TimeControlBase.h"

class SuddenDeathTimeControl : public TimeControlBase {
  
public:

  SuddenDeathTimeControl(uint32_t playersTime) : TimeControlBase( playersTime ) {
  }

};

#endif

