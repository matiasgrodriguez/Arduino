
#ifndef __SelectTimeControlUiHandler_h__
#define __SelectTimeControlUiHandler_h__

#include <avr/pgmspace.h>

#include "Buzzer.h"
#include "UiHandler.h"
#include "TimeControlUi.h"
#include "SelectTimeControlOptionUiHandler.h"

extern PushButton playerOneButton, playerTwoButton, okButton, backButton;
extern GameClockLcd lcd2;
extern Buzzer buzzer;

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
    okButton.tick( clock );
    backButton.tick( clock );
    
    if( okButton.wasPushed() ) {
      selectTimeControlOptionUiHandler.setTimeControlUi( timeControls[ currentTimeControlUi ] );
      currentUiHandler = &selectTimeControlOptionUiHandler;
      return;
    }
    
    if( playerOneButton.wasPushed() ) {
      if( currentTimeControlUi > 0 ) {
        currentTimeControlUi--;
      } else {
        do { currentTimeControlUi++; } while( timeControls[ currentTimeControlUi + 1 ] != NULL );
      }
      buzzer.beepFor( 150 );
    }
    if( playerTwoButton.wasPushed() ) {
      if( timeControls[ currentTimeControlUi + 1 ] != NULL ) {
        currentTimeControlUi++;
      } else {
        currentTimeControlUi = 0;
      }
      buzzer.beepFor( 150 );
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
