
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
    dumpState();
  }
  
  void selectPlayerOne() {
    if( isPlayerOnePlaying() ) {
      return;
    }
    if( isPlayerTwoPlaying() ) {
      onPlayerTwoPlayed();
    }
    onPlayerOneBeginToPlay();
  }
  
  void selectPlayerTwo() {
    if( isPlayerTwoPlaying() ) {
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
  
private:

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
  
  void dumpState() {
    Serial.print( "Clock time: " );Serial.print( clock->currentTime() );
    Serial.print( " Player one isPlaying: " );Serial.print( ( int )isPlayerOnePlaying() );Serial.print( " time: " );Serial.print( playerOne.getTime( clock ) );
    Serial.print( " Player two isPlaying: " );Serial.print( ( int )isPlayerTwoPlaying() );Serial.print( " time: " );Serial.println( playerTwo.getTime( clock ) );
  }

};

#endif

