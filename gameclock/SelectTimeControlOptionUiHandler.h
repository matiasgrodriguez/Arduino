
#ifndef __SelectTimeControlOptionUiHandler_h__
#define __SelectTimeControlOptionUiHandler_h__

#include <avr/pgmspace.h>

#include "UiHandler.h"
#include "GameClock.h"
#include "GameClockLcd.h"
#include "GameUiHandler.h"
#include "GameUiHandler.h"

extern PushButton playerOneButton, playerTwoButton, okButton, backButton;
extern GameClockLcd lcd2;

extern GameClock gameClock;

extern GameUiHandler gameUiHandler;
extern UiHandler *currentUiHandler;

class SelectTimeControlOptionUiHandler : public UiHandler {
  
  UiHandler *previusHandler;
  TimeControlUi *timeControlUi;
  int16_t currentOption;
  
public:

  SelectTimeControlOptionUiHandler() {
    timeControlUi = NULL;
    currentOption = 0;
  }
  
  virtual ~SelectTimeControlOptionUiHandler() {
  }

  virtual void tick(Clock *clock) {
    playerOneButton.tick( clock );
    playerTwoButton.tick( clock );
    okButton.tick( clock );
    backButton.tick( clock );
    
    if( okButton.wasPushed() ) {
      gameClock.setup( clock, timeControlUi->create( currentOption ) );
      gameUiHandler.setTimeControlUi( timeControlUi );
      currentUiHandler = &gameUiHandler;
      return;
    }
    
    if( backButton.wasPushed() ) {
      currentUiHandler = previusHandler;
      return;
    }

    if( playerOneButton.wasPushed() && currentOption > 0 ) {
      currentOption--;
    }
    if( playerTwoButton.wasPushed() && currentOption < timeControlUi->getNumberOfOptions() - 1 ) {
      currentOption++;
    }
  }
  
  virtual void render(Clock *clock){
    lcd2.beginRender();
    lcd2.printWholeScreen( timeControlUi->getOption( currentOption ) );
    lcd2.endRender();
  }
  
  void setTimeControlUi(TimeControlUi *timeControlUi) {
    if( this->timeControlUi != timeControlUi ) {
      currentOption = 0;
    }
    this->timeControlUi = timeControlUi;
  }

  void wire(UiHandler *previusHandler) {
    this->previusHandler = previusHandler;
  }

};

#endif
