
#ifndef __SelectTimeControlUiHandler_h__
#define __SelectTimeControlUiHandler_h__

#include <avr/pgmspace.h>
#include "UiHandler.h"
#include "TimeControlUi.h"

extern PushButton playerOneButton, playerTwoButton;
extern LiquidCrystal lcd;

extern TimeControlUi *timeControls[];

class SelectTimeControlUiHandler : public UiHandler {
  
  uint8_t currentTimeControlUi;
  
public:

  SelectTimeControlUiHandler() {
    currentTimeControlUi = 0;
  }
  
  virtual ~SelectTimeControlUiHandler() {
  }

  virtual void tick(Clock *clock) {
  }
  
  virtual void render(Clock *clock){
    uint8_t buffer[ 34 ];
    for(int i = 0; i < 34; ++i) {
      buffer[ i ] = ' ';
    }
    buffer[ 16 ] = '\0';
    buffer[ 33 ] = '\0';
    
    TimeControlUi *tc = timeControls[ 0 ];
    if( tc != NULL ) {
      const prog_char *name = tc->getName();
      char nameBuffer[17];
      strcpy_P( nameBuffer, name );
      int16_t length = strlen( nameBuffer );
      memcpy( &buffer[ 33 - length ], nameBuffer, length );
      //memcpy_P( buffer, name, str );
      //memcpy_P( &buffer[17], &name[16], 16 );
    }
    
    lcd.setCursor( 0, 0 );
    lcd.print( (const char*)buffer );
    lcd.setCursor( 0, 1 );
    lcd.print( (const char*)&buffer[17] );
  }

  
};

#endif
