
#ifndef __TimeControlBase_h__
#define __TimeControlBase_h__

#include "TimeControl.h"

class TimeControlBase : public TimeControl {

protected:

  TimeTracker *playerOne, *playerTwo;
  uint32_t playerOneInitialTime, playerTwoInitialTime;
  bool playerOneWon, playerTwoWon;

  TimeControlBase(uint32_t playerOneInitialTime, uint32_t playerTwoInitialTime) {
    playerOne = playerTwo = NULL;
    this->playerOneInitialTime = playerOneInitialTime;
    this->playerTwoInitialTime = playerTwoInitialTime;
    playerOneWon = playerTwoWon = false;
  }

public:

  virtual ~TimeControlBase() {
  }
  
  virtual void setup(TimeTracker *playerOne, TimeTracker *playerTwo) {
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
    
    playerOne->setTime( playerOneInitialTime );
    playerTwo->setTime( playerTwoInitialTime );
  }
  
  virtual void onPlayerOneBeganToPlay() {
  }
  
  virtual void onPlayerOnePlayed() {
  }
  
  virtual void onPlayerOneTimeExpired() {
    playerTwoWon = true;
  }
  
  virtual void onPlayerTwoBeganToPlay() { 
  }
  
  virtual void onPlayerTwoPlayed() {
  }
  
  virtual void onPlayerTwoTimeExpired() {
    playerOneWon = true;
  }
  
  virtual bool isOver() {
    return playerOneWon || playerTwoWon;
  }

};

#endif

