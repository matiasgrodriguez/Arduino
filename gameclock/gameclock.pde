
#include <MemoryFree.h>
#include <LiquidCrystal.h>

#include "base.h"

#include "GameClock.h"
#include "PushButton.h"
#include "GameClockLcd.h"
#include "ArduinoClock.h"

#include "SelectTimeControlUiHandler.h"
#include "SelectTimeControlOptionUiHandler.h"
#include "GameUiHandler.h"

#include "ByoYomiTimeControlUi.h"
#include "CanadianByoYomiTimeControlUi.h"
#include "FischerDelayTimeControlUi.h"
#include "BronsteinDelayTimeControlUi.h"
#include "HourGlassTimeControlUi.h"
#include "SuddenDeathTimeControlUi.h"
//#include "NormalDelayTimeControlUi.h"

//Hardware:
GameClockLcd lcd2(12, 11, 5, 4, 3, 2);
PushButton playerOneButton( 9 ), playerTwoButton( 8 ), okButton( 7 ), backButton( 6 );

//GameClock...
ArduinoClock clock;
GameClock gameClock;

//TimeControls:
TimeControlUi *timeControls[] = {
  new SuddenDeathTimeControlUi(),
  new HourGlassTimeControlUi(),
  new ByoYomiTimeControlUi(),
  new CanadianByoYomiTimeControlUi(),
  new FischerDelayTimeControlUi(),
  new BronsteinDelayTimeControlUi(),
  NULL
};

//User Interface ...
UiHandler *currentUiHandler;
SelectTimeControlUiHandler selectTimeControlUiHandler;
SelectTimeControlOptionUiHandler selectTimeControlOptionUiHandler;
GameUiHandler gameUiHandler;

void setup() {
  Serial.begin(9600);
  /*
  Serial.print( "GameClock: " );Serial.println( sizeof(GameClock) );
  Serial.print( "SuddenDeathTimeControl: " );Serial.println( sizeof( SuddenDeathTimeControl ) );
  Serial.print( "HourGlassTimeControl: " );Serial.println( sizeof( HourGlassTimeControl ) );
  Serial.print( "ByoYomiTimeControl: " );Serial.println( sizeof( ByoYomiTimeControl ) );
  Serial.print( "FischerDelayTimeControl: " );Serial.println( sizeof( FischerDelayTimeControl ) );
  Serial.print( "BronsteinDelayTimeControl: " );Serial.println( sizeof( BronsteinDelayTimeControl ) );
  Serial.print( "GameClockLcd: " );Serial.println( sizeof( GameClockLcd ) );
  */

  lcd2.init();
  playerOneButton.init();
  playerTwoButton.init();
  okButton.init();
  backButton.init();
  
  selectTimeControlOptionUiHandler.wire( &selectTimeControlUiHandler );
  currentUiHandler = &selectTimeControlUiHandler;

  Serial.print( "mem:" );Serial.println( freeMemory() ); 
}

void loop() {
  currentUiHandler->tick( &clock );
  currentUiHandler->render( &clock );
}

