
#ifndef __SelectTimeControlUiHandler_h__
#define __SelectTimeControlUiHandler_h__

#include <avr/pgmspace.h>
#include "UiHandler.h"
#include "TimeControlUi.h"
#include "SelectTimeControlOptionUiHandler.h"

extern PushButton playerOneButton, playerTwoButton, selectButton, backButton;
extern GameClockLcd lcd2;

extern TimeControlUi *timeControls[];

extern SelectTimeControlOptionUiHandler selectTimeControlOptionUiHandler;
extern UiHandler *currentUiHandler;

const prog_char SELECT_TIME_CONTROL_UI_HANDLER_MESSAGE[] PROGMEM = "Select game:";

class SelectTimeControlUiHandler : public UiHandler {
  
  uint8_t currentTimeControlUi;
  
public:

  SelectTimeControlUiHandler() {
    currentTimeControlUi = 0;
  }
  
  virtual ~SelectTimeControlUiHandler() {
  }

  virtual void tick(Clock *clock) {
    playerOneButton.tick( clock );
    playerTwoButton.tick( clock );
    selectButton.tick( clock );
    backButton.tick( clock );
    
    if( selectButton.wasPushed() ) {
      selectTimeControlOptionUiHandler.setTimeControlUi( timeControls[ currentTimeControlUi ] );
      currentUiHandler = &selectTimeControlOptionUiHandler;
      return;
    }
    
    if( playerOneButton.wasPushed() && currentTimeControlUi > 0 ) {
      currentTimeControlUi--;
    }
    if( playerTwoButton.wasPushed() && timeControls[ currentTimeControlUi + 1 ] != NULL ) {
      currentTimeControlUi++;
    }

  }
  
  virtual void render(Clock *clock){
    lcd2.beginRender();
    
    TimeControlUi *tc = timeControls[ currentTimeControlUi ];
    lcd2.printTopLeft( SELECT_TIME_CONTROL_UI_HANDLER_MESSAGE );
    if( tc != NULL ) {
      lcd2.printBottomRight( tc->getName() );
    }
    
    lcd2.endRender();
  }

  
};

#endif
