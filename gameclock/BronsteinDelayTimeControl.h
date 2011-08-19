
#ifndef __BronsteinDelayTimeControl_h__
#define __BronsteinDelayTimeControl_h__

#include "TimeControlBase.h"

class BronsteinDelayTimeControl : public TimeControlBase {
  
  uint32_t delay;
  
public:

  BronsteinDelayTimeControl(uint32_t playersTime, uint32_t delay) : TimeControlBase( playersTime, playersTime ) {
    this->delay = delay;
  }
  
  virtual ~BronsteinDelayTimeControl() {
  }
  
  virtual void onPlayerOnePlayed() {
    onPlayerPlayed( playerOne );
  }

  virtual void onPlayerTwoPlayed() { 
    onPlayerPlayed( playerTwo );
  }
  
private:

  void onPlayerPlayed(TimeTracker *player) {
    int32_t playTime = player->getLastConsumedTime();
    if( playTime <= delay ) {
      player->addTime( playTime );
    }
  }
  
};

#endif

