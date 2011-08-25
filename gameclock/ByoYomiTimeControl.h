
#ifndef __ByoYomiTimeControl_h__
#define __ByoYomiTimeControl_h__

#include "TimeControlBase.h"

#define BYO_YOMI_SETUP_MAX_PERIODS  5

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
  
  class PlayerState;
  
public:

  ByoYomiTimeControl(ByoYomiSetup byoYomiSetup) : TimeControlBase( byoYomiSetup.time, byoYomiSetup.time ), setup( byoYomiSetup ), playerOneState( &setup ), playerTwoState( &setup ) {
  }
  
  virtual ~ByoYomiTimeControl() {
  }
  
  //<TimeControl>
  
  virtual void onPlayerOnePlayed() {
    onPlayerPlayed( playerOne, &playerOneState );
  }
  
  virtual void onPlayerOneTimeExpired() {
    onPlayerTimeExpired( playerOne, &playerOneState );
  }
  
  virtual void onPlayerTwoPlayed() {
    onPlayerPlayed( playerTwo, &playerTwoState );
  }

  virtual void onPlayerTwoTimeExpired() {
    onPlayerTimeExpired( playerTwo, &playerTwoState );
  }

  //</TimeControl>
  
  bool isPlayerOneInNormalTime() {
    return !isPlayerOnByoYomi( &playerOneState );
  }

  uint16_t getPlayerOneRemainingByoYomiPeriods() {
    return setup.numberOfPeriods - playerOneState.getPeriod();
  }

  uint16_t getPlayerOneRemainingNumberOfPlays() {
    return setup.periods[ playerOneState.getPeriod() ].numberOfPlays - playerOneState.getNumberOfPlays();
  }
  
  bool isPlayerTwoInNormalTime() {
    return !isPlayerOnByoYomi( &playerTwoState );
  }

  uint16_t getPlayerTwoRemainingByoYomiPeriods() {
    return setup.numberOfPeriods - playerTwoState.getPeriod();
  }

  uint16_t getPlayerTwoRemainingNumberOfPlays() {
    return setup.periods[ playerTwoState.getPeriod() ].numberOfPlays - playerTwoState.getNumberOfPlays();
  }

private:

  ByoYomiTimeControl() : TimeControlBase( 0, 0 ), setup(), playerOneState( NULL ), playerTwoState( NULL ) {
  }

  void onPlayerPlayed(TimeTracker *player, PlayerState *playerState) {
    if( !isPlayerOnByoYomi( playerState ) ) {
      return;
    }
    playerIncrementNumberOfPlayes( playerState );
    if( hasPlayerReachedTargetNumberOfPlays( playerState ) ) {
      playerRenewByoYomiPeriod( player, playerState );
    }
  }

  bool isPlayerOnByoYomi(PlayerState *playerState) {
    return playerState->isOnByoYomi();
  }
  
  void playerIncrementNumberOfPlayes(PlayerState *playerState) {
    playerState->incrementNumberOfPlays();
  }
  
  bool hasPlayerReachedTargetNumberOfPlays(PlayerState *playerState) {
    return playerState->hasReachedNumberOfPlays();
  }
  
  void playerRenewByoYomiPeriod(TimeTracker *player, PlayerState *playerState) {
    playerState->resetNumberOfPlays();
    setPlayerTime( player, playerState );
  }
  
  void onPlayerTimeExpired(TimeTracker *player, PlayerState *playerState) {
    if( !isPlayerOnByoYomi( playerState ) ) {
      playerNormalPeriodEnded( playerState );
    } else {
      playerMoveToNextByoYomiPeriod( playerState );
    }
    playerBeginByoYomiPeriodOrEndGame( player, playerState );
  }
  
  void playerNormalPeriodEnded(PlayerState *playerState) {
    playerState->beginByoYomi();
  }
  
  void playerMoveToNextByoYomiPeriod(PlayerState *playerState) {
    playerState->nextByoYomi();
  }
  
  void playerBeginByoYomiPeriodOrEndGame(TimeTracker *player, PlayerState *playerState) {
    if( playerState->isInValidByoYomiPeriod() ) {
      setPlayerTime( player, playerState );
    } else {
      if( playerOne == player ) {
        playerTwoWon = true;
      } else {
        playerOneWon = true;
      }
    }
  }
  
  void setPlayerTime(TimeTracker *player, PlayerState *playerState) {
    player->setTime( playerState->getTime() );
  }
  

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
  
    uint16_t getNumberOfPlays() {
      return numberOfPlays;
    }

    uint16_t getPeriod() {
      return period;
    }

  };

  ByoYomiSetup setup;
  PlayerState playerOneState, playerTwoState;
  
};

#endif

