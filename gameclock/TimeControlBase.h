
#ifndef __TimeControlBase_h__
#define __TimeControlBase_h__

#include "TimeControl.h"

class TimeControlBase : TimeControl {

protected:

  TimeTracker *playerOne, *playerTwo;

  TimeControlBase() {
  }

public:

  virtual ~TimeControlBase() {
  }
  
  virtual void setup(TimeTracker *playerOne, TimeTracker *playerTwo) {
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
  }
  
  virtual void onPlayerOneBeganToPlay() {
  }
  
  virtual void onPlayerOnePlayed() {
  }
  
  virtual void onPlayerOneTimeExpired() {
  }
  
  virtual void onPlayerTwoBeganToPlay() { 
  }
  
  virtual void onPlayerTwoPlayed() {
  }
  
  virtual void onPlayerTwoTimeExpired() {
  }

};

#endif

