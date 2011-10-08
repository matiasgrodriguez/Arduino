
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

const prog_char gameUiHandlerPlayerOneWinnerMessage[] PROGMEM = "WINNER ";
const prog_char gameUiHandlerPlayerTwoWinnerMessage[] PROGMEM = " WINNER";

void(* resetFunc) (void) = 0; //declare reset function @ address 0

class GameUiHandler : public UiHandler {
  
  TimeControlUi *timeControlUi;
  
public:

  virtual void tick(Clock *clock) {
    buttonGestures.tick( clock );
    gameClock.tick();
    
    if( buttonGestures.wasButtonThreePressed() ) {
      if( gameClock.isOver() ) {
        resetFunc();
      } else if( gameClock.isPaused() ) {
        lcd2.setBlinking( false );
        gameClock.resume();
      } else {
        lcd2.setBlinking( true );
        gameClock.pause();
      }
      return;
    }

    if( buttonGestures.wasButtonOnePressed() ) {
      gameClock.selectPlayerTwo();
    } else if( buttonGestures.wasButtonTwoPressed() ) {
      gameClock.selectPlayerOne();
    }
 
  }
  
  virtual void render(Clock *clock) {
    lcd2.beginRender( clock );
    timeControlUi->renderGame( &gameClock, &lcd2 );
    if( gameClock.isOver() ) {
      if( gameClock.playerOneWon() ) {
        lcd2.printBottomLeft( gameUiHandlerPlayerOneWinnerMessage );
      } else if( gameClock.playerTwoWon() ) {
        lcd2.printBottomRight( gameUiHandlerPlayerTwoWinnerMessage );
      }
    }
    lcd2.endRender();
  }
  
  void setTimeControlUi(TimeControlUi *timeControlUi) {
    this->timeControlUi = timeControlUi;
  }
  
};

#endif

