
#ifndef __GameClock_h__
#define __GameClock_h__

#include "Clock.h"
#include "TimeControl.h"
#include "TimeTrackerImpl.h"
#include "Buzzer.h"

extern Buzzer buzzer;

class GameClock {
  
  Clock *clock;
  TimeControl *timeControl;
  TimeTrackerImpl playerOne, playerTwo;
  
  TimeTrackerImpl *currentPlayer;
  bool paused;
  bool overNotified;
  
public:

  GameClock() {
    clock = NULL;
    currentPlayer = NULL;
    paused = false;
    overNotified = false;
  }
  
  virtual ~GameClock() {
  }
  
  void setup(Clock *clock, TimeControl *timeControl) {
    this->clock = clock;
    this->timeControl = timeControl;
    
    this->timeControl->setup( &playerOne, &playerTwo );
  }
  
  void tick() {
    if( isOver() && overWasNotNotified() ) {
      onOver();
    }
    if( isPaused() || isOver() ) {
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
    if( isOver() || isPaused() || isPlayerOnePlaying() ) {
      return;
    }
    if( isPlayerTwoPlaying() ) {
      onPlayerTwoPlayed();
    }
    onPlayerOneBeginToPlay();
  }
  
  void selectPlayerTwo() {
    if( isOver() || isPaused() || isPlayerTwoPlaying() ) {
      return;
    }
    if( isPlayerOnePlaying() ) {
      onPlayerOnePlayed();
    }
    onPlayerTwoBeginToPlay();
  }
  
  void pause() {
    if( currentPlayer == NULL || isPaused() || isOver() ) {
      return;
    }
    currentPlayer->beginPause( clock );
    paused = true;
    beep();
  }
  
  void resume() {
    if( isOver() || !isPaused() ) {
      return;
    }
    currentPlayer->endPause( clock );
    paused = false;
    beep();
  }
  
  Clock *getClock() {
    return clock;
  }
  
  TimeControl *getTimeControl() {
    return timeControl;
  }
  
  bool isPaused() {
    return paused;
  }

  bool isOver() {
    return timeControl != NULL && timeControl->isOver();
  }

  bool isPlayerOnePlaying() {
    return currentPlayer == &playerOne;
  }
  
  bool isPlayerTwoPlaying() {
    return currentPlayer == &playerTwo;
  }
  
private:

  void onPlayerOneBeginToPlay() {
    currentPlayer = &playerOne;
    currentPlayer->mark( clock );
    timeControl->onPlayerOneBeganToPlay();
    beep();
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
  
  void onPlayerTwoPlayed() {
    currentPlayer->consume( clock );
    timeControl->onPlayerTwoPlayed();
  }

  void onPlayerTwoBeginToPlay() {
    currentPlayer = &playerTwo;
    currentPlayer->mark( clock );
    timeControl->onPlayerTwoBeganToPlay();
    beep();
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
  
  bool overWasNotNotified() {
    return !overNotified;
  }

  void onOver() {
    buzzer.playTone( 3520, 2000 );
    overNotified = true;
    currentPlayer = NULL;
  }
  
  void beep() {
    buzzer.playTone( 880, 250 );
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

