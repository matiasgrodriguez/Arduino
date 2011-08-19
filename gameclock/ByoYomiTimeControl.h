
#ifndef __ByoYomiTimeControl_h__
#define __ByoYomiTimeControl_h__

#include "TimeControlBase.h"

#define BYO_YOMI_SETUP_MAX_PERIODS  4

struct ByoYomiPeriod {
  
  uint16_t numberOfPlays;
  uint32_t time;
  
  ByoYomiPeriod() {
    numberOfPlays = 0;
    time = 0;
  }
  
};

struct ByoYomiSetup {
  uint32_t time;
  uint16_t numberOfPeriods;
  ByoYomiPeriod periods[ BYO_YOMI_SETUP_MAX_PERIODS ];
};


class ByoYomiTimeControl : public TimeControlBase {
    
  class PlayerState {

    bool onByoYomi;
    uint16_t period;
    uint16_t numberOfPlays;
    ByoYomiSetup *setup;
    
  public:
    
    PlayerState(ByoYomiSetup *setup) {
      this->setup = setup;
      onByoYomi = false;
      period = 0;
      numberOfPlays = 0;
    }
    
    bool isOnByoYomi() {
      return onByoYomi;
    }
    
    void incrementNumberOfPlays() {
      numberOfPlays++;
    }
    
    bool hasReachedNumberOfPlays() {
      return numberOfPlays == setup->periods[ period ].numberOfPlays;
    }
    
    void resetNumberOfPlays() {
      numberOfPlays = 0;
    }
    
    uint32_t getTime() {
      return setup->periods[ period ].time;
    }
    
    void beginByoYomi() {
      onByoYomi = true;
    }
    
    void nextByoYomi() {
      period++;
      resetNumberOfPlays();
    }
    
    bool isInValidByoYomiPeriod() {
      return period < setup->numberOfPeriods;
    }
    
private:
    

  };
  
  ByoYomiSetup setup;
  PlayerState playerOneState, playerTwoState;
  
public:

  ByoYomiTimeControl(ByoYomiSetup byoYomiSetup) : TimeControlBase( byoYomiSetup.time, byoYomiSetup.time ), setup( byoYomiSetup ), playerOneState( &setup ), playerTwoState( &setup ) {
    Serial.print( setup.time );Serial.print( " " );Serial.println( setup.numberOfPeriods );
  }
  
  virtual ~ByoYomiTimeControl() {
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
  
  virtual void onPlayerOneTimeExpired() {
    if( !isPlayerOneOnByoYomi() ) {
      playerOneNormalPeriodEnded();
    } else {
      playerOneMoveToNextByoYomiPeriod();
    }
    playerOneBeginByoYomiPeriodOrEndGame();
  }


private:

  ByoYomiTimeControl() : TimeControlBase( 1000, 1000 ), setup(), playerOneState( NULL ), playerTwoState( NULL ) {
  }

  bool isPlayerOneOnByoYomi() {
    return playerOneState.isOnByoYomi();
  }
  
  void playerOneIncrementNumberOfPlayes() {
    playerOneState.incrementNumberOfPlays();
  }
  
  bool hasPlayerOneReachedTargetNumberOfPlays() {
    return playerOneState.hasReachedNumberOfPlays();
  }
  
  void playerOneRenewByoYomiPeriod() {
    playerOneState.resetNumberOfPlays();
    setPlayerOneTime();
  }
  
  void playerOneNormalPeriodEnded() {
    playerOneState.beginByoYomi();
  }
  
  void playerOneMoveToNextByoYomiPeriod() {
    playerOneState.nextByoYomi();
  }
  
  void playerOneBeginByoYomiPeriodOrEndGame() {
    if( playerOneState.isInValidByoYomiPeriod() ) {
      setPlayerOneTime();
    } else {
      playerTwoWon = true;
    }
  }
  
  void setPlayerOneTime() {
    playerOne->setTime( playerOneState.getTime() );
  }
  
};

#endif

