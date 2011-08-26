
#ifndef __GameUiHandler_h__
#define __GameUiHandler_h__

#include "GameClock.h"
#include "PushButton.h"
#include "UiHandler.h"
#include "TimeControlUi.h"

extern GameClock gameClock;
extern PushButton playerOneButton, playerTwoButton;
extern LiquidCrystal lcd;

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
  }
  
  virtual void render(Clock *clock) {
    uint8_t buffer[ 34 ];
    for(int i = 0; i < 34; ++i) {
      buffer[ i ] = ' ';
    }
    buffer[ 16 ] = '\0';
    buffer[ 33 ] = '\0';
    
    timeControlUi->render( clock, gameClock.getTimeControl(), buffer, &buffer[17] );
    lcd.setCursor( 0, 0 );
    lcd.print( (const char*)buffer );
    lcd.setCursor( 0, 1 );
    lcd.print( (const char*)&buffer[17] );
  }
  
  void setTimeControlUi(TimeControlUi *timeControlUi) {
    this->timeControlUi = timeControlUi;
  }
  
};

#endif

