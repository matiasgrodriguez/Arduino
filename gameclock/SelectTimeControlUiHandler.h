
#ifndef __SelectTimeControlUiHandler_h__
#define __SelectTimeControlUiHandler_h__

#include <avr/pgmspace.h>

#include "UiHandler.h"
#include "TimeControlUi.h"
#include "GameButtonGestures.h"
#include "SelectTimeControlOptionUiHandler.h"

extern GameButtonGestures buttonGestures;
extern GameClockLcd lcd2;

extern TimeControlUi *timeControls[];

extern SelectTimeControlOptionUiHandler selectTimeControlOptionUiHandler;
extern UiHandler *currentUiHandler;

const prog_char SELECT_TIME_CONTROL_UI_HANDLER_LEFT_MESSAGE[] PROGMEM = "Next";
const prog_char SELECT_TIME_CONTROL_UI_HANDLER_RIGHT_MESSAGE[] PROGMEM = "OK";

class SelectTimeControlUiHandler : public UiHandler {
  
  uint8_t currentTimeControlUi;
  
public:

  SelectTimeControlUiHandler() {
    currentTimeControlUi = 0;
  }
  
  virtual ~SelectTimeControlUiHandler() {
  }

  virtual void tick(Clock *clock) {
    buttonGestures.tick( clock );
    
    if( buttonGestures.wasButtonOnePressed() ) {
      if( timeControls[ currentTimeControlUi + 1 ] != NULL ) {
        currentTimeControlUi++;
      } else {
        currentTimeControlUi = 0;
      }
      beep();
    }
    
    if( buttonGestures.wasButtonTwoPressed() ) {
      selectTimeControlOptionUiHandler.setTimeControlUi( timeControls[ currentTimeControlUi ] );
      currentUiHandler = &selectTimeControlOptionUiHandler;
      beep();
    }

  }
  
  virtual void render(Clock *clock){
    lcd2.beginRender( clock );
    
    TimeControlUi *tc = timeControls[ currentTimeControlUi ];
    lcd2.printTopLeft( SELECT_TIME_CONTROL_UI_HANDLER_LEFT_MESSAGE );
    lcd2.printTopRight( SELECT_TIME_CONTROL_UI_HANDLER_RIGHT_MESSAGE );
    lcd2.printBottomCenter( tc->getName() );

    lcd2.endRender();
  }
  
};

#endif
