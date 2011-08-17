
#ifndef __TimeControl_h__
#define __TimeControl_h__

#include "TimeTracker.h"

class TimeControl {

public:

  virtual void setup(TimeTracker *playerOne, TimeTracker *playerTwo) = 0;

  virtual void onPlayerOneBeganToPlay() = 0;
  virtual void onPlayerOnePlayed() = 0;
  virtual void onPlayerOneTimeExpired() = 0;

  virtual void onPlayerTwoBeganToPlay() = 0;
  virtual void onPlayerTwoPlayed() = 0;
  virtual void onPlayerTwoTimeExpired() = 0;
  
  virtual bool isOver() = 0;

};

#endif

