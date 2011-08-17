
#ifndef __HourGlassTimeControl_h__
#define __HourGlassTimeControl_h__

#include "TimeControlBase.h"

class HourGlassTimeControl : public TimeControlBase {
  
  uint32_t time;
  
public:

  HourGlassTimeControl(uint32_t playersTime) : TimeControlBase( playersTime, playersTime ) {
  }
  
  virtual ~HourGlassTimeControl() {
  }

  virtual void onPlayerOnePlayed() {
    transferTime( playerOne, playerTwo );
  }
  
  virtual void onPlayerOneTimeExpired() {
    transferTime( playerOne, playerTwo );
    TimeControlBase::onPlayerOneTimeExpired();
  }

  virtual void onPlayerTwoPlayed() {
    transferTime( playerTwo, playerOne );
  }
  
  virtual void onPlayerTwoTimeExpired() {
    transferTime( playerTwo, playerOne );
    TimeControlBase::onPlayerTwoTimeExpired();
  }

private:

  void transferTime(TimeTracker *from, TimeTracker *to) {
    to->addTime( from->getLastConsumedTime() );
  }
  
};

#endif

