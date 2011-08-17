
#ifndef __ByoYomiTimeControl_h__
#define __ByoYomiTimeControl_h__

#include "TimeControlBase.h"

#define BYO_YOMI_SETUP_MAX_PERIODS  10

struct ByoYomiPeriod {
  
  uint16_t numberOfPlays;
  uint32_t time;
  
  ByoYomiPeriod() {
    numberOfPlays = 0;
    time = 0;
  }
  
  ByoYomiPeriod(uint32_t numberOfPlays, uint32_t time) {
    numberOfPlays = numberOfPlays;
    time = time;
  }
  
};

struct ByoYomiSetup {
  uint32_t time;
  ByoYomiPeriod periods[ BYO_YOMI_SETUP_MAX_PERIODS ];
};


class ByoYomiTimeControl : public TimeControlBase {
    
  class PlayerState {

    bool onByoYomi;
    uint16_t period;
    uint16_t numberOfPlays;
    
  public:
    
    PlayerState() {
      onByoYomi = true;
      period = 0;
      numberOfPlays = 0;
    }
    
    bool isOnByoYomi() {
      return onByoYomi;
    }
    
    void incrementNumberOfPlays() {
      numberOfPlays++;
    }

  };
  
  ByoYomiSetup setup;
  PlayerState playerOneState, playerTwoState;
  
public:

  ByoYomiTimeControl(ByoYomiSetup byoYomiSetup) : TimeControlBase( byoYomiSetup.time, byoYomiSetup.time ) {
    setup = byoYomiSetup;
  }
  
  virtual void onPlayerOnePlayed() {
    if( !isPlayerOneOnByoYomi() ) {
      return;
    }
    playerOneIncrementNumberOfPlayes();
    if( hasPlayerOneReachedTargetNumberOfPlays() ) {
      playerOneRenewByoYomiPeriod();
    }
  } 

private:

  bool isPlayerOneOnByoYomi() {
    return playerOneState.isOnByoYomi();
  }
  
  void playerOneIncrementNumberOfPlayes() {
    playerOneState.incrementNumberOfPlays();
  }
  
  bool hasPlayerOneReachedTargetNumberOfPlays() {
    return false;
  }
  
  void playerOneRenewByoYomiPeriod() {
  }
  
};

#endif

