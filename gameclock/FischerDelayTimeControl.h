
#ifndef __FischerDelayTimeControl_h__
#define __FischerDelayTimeControl_h__

#include "TimeControlBase.h"

class FischerDelayTimeControl : public TimeControlBase {
  
  uint32_t bonus;
  
public:

  FischerDelayTimeControl(uint32_t playersTime, uint32_t playBonus) : TimeControlBase( playersTime, playersTime ) {
    bonus = playBonus;
  }
  
  virtual ~FischerDelayTimeControl() {
  }
  
  virtual void onPlayerOnePlayed() {
    playerOne->addTime( bonus );
  }

  virtual void onPlayerTwoBeganToPlay() { 
    playerTwo->addTime( bonus );
  }
  
};

#endif

