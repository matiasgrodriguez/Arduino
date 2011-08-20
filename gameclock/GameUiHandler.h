
#ifndef __GameUiHandler_h__
#define __GameUiHandler_h__

#include "GameClock.h"
#include "PushButton.h"
#include "UiHandler.h"

extern GameClock gameClock;
extern PushButton playerOneButton, playerTwoButton;

class GameUiHandler : public UiHandler {
  
public:

  virtual void tick(Clock *clock) {
    playerOneButton.tick( clock );
    playerTwoButton.tick( clock );
    gameClock.tick();
    
    if( playerOneButton.wasPushed() ) {
      gameClock.selectPlayerTwo();
    } else if( playerTwoButton.wasPushed() ) {
      gameClock.selectPlayerOne();
    }
  }
  
};

#endif

