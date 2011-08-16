
#ifndef __TimeControlTest_h__
#define __TimeControlTest_h__

#include "TimeControl.h"

class TimeControlTest : public TimeControl {
  
  int32_t playerOneInitialTime;
  int32_t playerTwoInitialTime;
  
public:

  TimeControlTest(int32_t playerOneInitialTime, int32_t playerTwoInitialTime) {
    this->playerOneInitialTime = playerOneInitialTime;
    this->playerTwoInitialTime = playerTwoInitialTime;
  }
  
  virtual ~TimeControlTest() {
  }

  virtual void setup(TimeTracker *playerOne, TimeTracker *playerTwo) {
    Serial.println( "setup" );
    playerOne->setTime( playerOneInitialTime );
    playerTwo->setTime( playerTwoInitialTime );
  }
  
  virtual void onPlayerOneBeganToPlay() {
    Serial.println( "onPlayerOneBeganToPlay" );
  }
  
  virtual void onPlayerOnePlayed(){ 
    Serial.println( "onPlayerOnePlayed" );
  }
  
  virtual void onPlayerOneTimeExpired(){
    Serial.println( "onPlayerOneTimeExpired" );
  }
  
  virtual void onPlayerTwoBeganToPlay(){ 
    Serial.println( "onPlayerTwoBeganToPlay" );
  }
  
  virtual void onPlayerTwoPlayed(){ 
    Serial.println( "onPlayerTwoPlayed" );
  }
  
  virtual void onPlayerTwoTimeExpired() {
    Serial.println( "onPlayerTwoTimeExpired" );
  }
  
};

#endif

