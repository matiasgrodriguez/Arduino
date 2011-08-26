
#ifndef __HourGlassTimeControl_h__
#define __HourGlassTimeControl_h__

#include "TimeControlBase.h"

class HourGlassTimeControl : public TimeControlBase {
  
  uint32_t lastTransferredTime;
  bool lastTransferedTimeWasFromPlayerOne;
  
public:

  HourGlassTimeControl(uint32_t playersTime) : TimeControlBase( playersTime, playersTime ) {
    lastTransferredTime = 0;
    lastTransferedTimeWasFromPlayerOne = false;
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
  
  uint32_t getLastTransferedTime() {
    return lastTransferredTime;
  }
  
  bool wasTimeTransferredFromPlayerOne() {
    return lastTransferedTimeWasFromPlayerOne;
  }

private:

  void transferTime(TimeTracker *from, TimeTracker *to) {
    lastTransferredTime = from->getLastConsumedTime();
    lastTransferedTimeWasFromPlayerOne = from == playerOne;
    to->addTime( lastTransferredTime );
  }
  
};

#endif

