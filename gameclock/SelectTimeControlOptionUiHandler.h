
#ifndef __SelectTimeControlOptionUiHandler_h__
#define __SelectTimeControlOptionUiHandler_h__

#include <avr/pgmspace.h>
#include "UiHandler.h"
#include "TimeControlUi.h"
#include "GameUiHandler.h"

extern PushButton playerOneButton, playerTwoButton, selectButton, backButton;
extern LiquidCrystal lcd;

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
    selectButton.tick( clock );
    backButton.tick( clock );
    
    if( selectButton.wasPushed() ) {
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
    uint8_t buffer[ 34 ];
    for(int i = 0; i < 34; ++i) {
      buffer[ i ] = ' ';
    }
    buffer[ 16 ] = '\0';
    buffer[ 33 ] = '\0';
    
    char nameBuffer[33];
    const prog_char *option = timeControlUi->getOption( currentOption );
    memcpy_P( nameBuffer, option, 33 );
    memcpy( buffer, nameBuffer, 16 );
    memcpy( &buffer[ 17 ], &nameBuffer[16], 16 );
    
    lcd.setCursor( 0, 0 );
    lcd.print( (const char*)buffer );
    lcd.setCursor( 0, 1 );
    lcd.print( (const char*)&buffer[17] );
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
