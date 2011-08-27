
#ifndef __SelectTimeControlUiHandler_h__
#define __SelectTimeControlUiHandler_h__

#include <avr/pgmspace.h>
#include "UiHandler.h"
#include "TimeControlUi.h"
#include "SelectTimeControlOptionUiHandler.h"

extern PushButton playerOneButton, playerTwoButton, selectButton, backButton;
extern LiquidCrystal lcd;

extern TimeControlUi *timeControls[];

extern SelectTimeControlOptionUiHandler selectTimeControlOptionUiHandler;
extern UiHandler *currentUiHandler;

const prog_char SELECT[] PROGMEM = "Select game:";

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
    uint8_t buffer[ 34 ];
    for(int i = 0; i < 34; ++i) {
      buffer[ i ] = ' ';
    }
    buffer[ 16 ] = '\0';
    buffer[ 33 ] = '\0';
    
    TimeControlUi *tc = timeControls[ currentTimeControlUi ];

    if( tc != NULL ) {
      char nameBuffer[17];
      strcpy_P( nameBuffer, SELECT );
      int16_t length = strlen( nameBuffer );
      memcpy( buffer, nameBuffer, length );
      
      const prog_char *name = tc->getName();
      strcpy_P( nameBuffer, name );
      length = strlen( nameBuffer );
      memcpy( &buffer[ 33 - length ], nameBuffer, length );
    }
    
    lcd.setCursor( 0, 0 );
    lcd.print( (const char*)buffer );
    lcd.setCursor( 0, 1 );
    lcd.print( (const char*)&buffer[17] );
  }

  
};

#endif
