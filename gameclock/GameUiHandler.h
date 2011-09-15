
#ifndef __GameUiHandler_h__
#define __GameUiHandler_h__

#include "PushButton.h"
#include "GameClock.h"
#include "GameClockLcd.h"
#include "UiHandler.h"
#include "TimeControlUi.h"
#include "Buzzer.h"

extern GameClock gameClock;
extern PushButton playerOneButton, playerTwoButton;
extern GameClockLcd lcd2;

class GameUiHandler : public UiHandler {
  
  TimeControlUi *timeControlUi;
  
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
    
    /*
    if( backButton.wasPushed() ) {
      gameClock.pause();
    } else if( okButton.wasPushed() ) {
      gameClock.resume();
    }
    */
  }
  
  virtual void render(Clock *clock) {
    lcd2.beginRender();
    timeControlUi->renderGame( &gameClock, &lcd2 );
    lcd2.endRender();
  }
  
  void setTimeControlUi(TimeControlUi *timeControlUi) {
    this->timeControlUi = timeControlUi;
  }
  
};

#endif

