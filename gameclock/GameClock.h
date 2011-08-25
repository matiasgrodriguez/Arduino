
#ifndef __GameClock_h__
#define __GameClock_h__

#include "Clock.h"
#include "TimeControl.h"
#include "TimeTrackerImpl.h"

class GameClock {
  
  Clock *clock;
  TimeControl *timeControl;
  TimeTrackerImpl playerOne, playerTwo;
  
  TimeTrackerImpl *currentPlayer;
  
public:

  GameClock() {
    clock = NULL;
    timeControl = NULL;
    currentPlayer = NULL;
  }
  
  virtual ~GameClock() {
  }
  
  void setup(Clock *clock, TimeControl *timeControl) {
    this->clock = clock;
    this->timeControl = timeControl;
    
    this->timeControl->setup( &playerOne, &playerTwo );
  }
  
  void tick() {
    if( isOver() ) {
      return;
    }
    if( isPlayerOnePlaying() ) {
      checkIfPlayerOneTimeExpired();
    } else if( isPlayerTwoPlaying() ) {
      checkIfPlayerTwoTimeExpired();
    }
    dumpState();
  }
  
  void selectPlayerOne() {
    if( isOver() || isPlayerOnePlaying() ) {
      return;
    }
    if( isPlayerTwoPlaying() ) {
      onPlayerTwoPlayed();
    }
    onPlayerOneBeginToPlay();
  }
  
  void selectPlayerTwo() {
    if( isOver() || isPlayerTwoPlaying() ) {
      return;
    }
    if( isPlayerOnePlaying() ) {
      onPlayerOnePlayed();
    }
    onPlayerTwoBeginToPlay();
  }
  
  void pause() {
  }
  
  void resume() {
  }
  
  Clock *getClock() {
    return clock;
  }
  
  TimeControl *getTimeControl() {
    return timeControl;
  }
  
private:

  bool isOver() {
    return timeControl != NULL && timeControl->isOver();
  }

  bool isPlayerOnePlaying() {
    return currentPlayer == &playerOne;
  }
  
  void onPlayerOneBeginToPlay() {
    currentPlayer = &playerOne;
    currentPlayer->mark( clock );
    timeControl->onPlayerOneBeganToPlay();
  }

  void onPlayerOnePlayed() {
    currentPlayer->consume( clock );
    timeControl->onPlayerOnePlayed();
  }
  
  void checkIfPlayerOneTimeExpired() {
    if( playerOne.getTime( clock ) > 0 ) {
      return;
    }
    if( playerOne.onlyOnceIsExpired() ) {
      playerOne.consume( clock );
      playerOne.mark( clock );
      timeControl->onPlayerOneTimeExpired();
    }
  }

  bool isPlayerTwoPlaying() {
    return currentPlayer == &playerTwo;
  }
  
  void onPlayerTwoPlayed() {
    currentPlayer->consume( clock );
    timeControl->onPlayerTwoPlayed();
  }

  void onPlayerTwoBeginToPlay() {
    currentPlayer = &playerTwo;
    currentPlayer->mark( clock );
    timeControl->onPlayerTwoBeganToPlay();
  }
  
  void checkIfPlayerTwoTimeExpired() {
    if( playerTwo.getTime( clock ) > 0 ) {
      return;
    }
    if( playerTwo.onlyOnceIsExpired() ) {
      playerTwo.consume( clock );
      playerTwo.mark( clock );
      timeControl->onPlayerTwoTimeExpired();
    }
  }
  
  void dumpState() {
    /*
    Serial.print( "Clock time: " );Serial.print( clock->currentTime() );Serial.print( " isOver: " );Serial.print( ( int )isOver() );
    Serial.print( " Player one isPlaying: " );Serial.print( ( int )isPlayerOnePlaying() );Serial.print( " time: " );Serial.print( playerOne.getTime( clock ) );
    Serial.print( " Player two isPlaying: " );Serial.print( ( int )isPlayerTwoPlaying() );Serial.print( " time: " );Serial.println( playerTwo.getTime( clock ) );
    //*/
  }

};

#endif

