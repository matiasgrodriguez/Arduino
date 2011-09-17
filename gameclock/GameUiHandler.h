
#ifndef __GameUiHandler_h__
#define __GameUiHandler_h__

#include "GameClock.h"
#include "GameClockLcd.h"
#include "UiHandler.h"
#include "TimeControlUi.h"
#include "GameButtonGestures.h"
#include "Buzzer.h"

extern GameClock gameClock;
extern GameButtonGestures buttonGestures;
extern GameClockLcd lcd2;

class GameUiHandler : public UiHandler {
  
  TimeControlUi *timeControlUi;
  
public:

  virtual void tick(Clock *clock) {
    buttonGestures.tick( clock );
    gameClock.tick();
    
    if( buttonGestures.wasButtonOnePressed() ) {
      gameClock.selectPlayerTwo();
      return;
    }
    
    if( buttonGestures.wasButtonTwoPressed() ) {
      gameClock.selectPlayerOne();
      return;
    }
    
    if( buttonGestures.wasButtonOneAndTwoPressed() ) {
      if( gameClock.isOver() ) {
        //reset
      } else if( gameClock.isPaused() ) {
        gameClock.resume();
      } else {
        gameClock.pause();
      }
    }
 
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

