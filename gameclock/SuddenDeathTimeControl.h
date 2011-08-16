
#ifndef __SuddenDeathTimeControl_h__
#define __SuddenDeathTimeControl_h__

#include "TimeControlBase.h"

class SuddenDeathTimeControl : TimeControlBase {
  
  uint32_t time;
  
public:

  SuddenDeathTimeControl(uint32_t playersTime) {
    time = playersTime;
  }
  
  virtual void setup(TimeTracker *playerOne, TimeTracker *playerTwo) {
    TimeControlBase::setup( playerOne, playerTwo );
    
    playerOne->setTime( time );
    playerTwo->setTime( time );
  }
  
  virtual void onPlayerOneTimeExpired() {
  }
  
  virtual void onPlayerTwoTimeExpired() {
  }

};

#endif

