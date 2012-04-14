
#include <MemoryFree.h>
#include <LiquidCrystal.h>

#include "base.h"

#include "GameClock.h"
#include "PushButton.h"
#include "Buzzer.h"
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
GameClockLcd lcd2( 7, 6, 5, 4, 3, 2);
PushButton playerOneButton( 8 ), playerTwoButton( 10 ), menuButton( 9 );
Buzzer buzzer( 12 );

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
GameButtonGestures buttonGestures;

void setup() {
  //Serial.begin(9600);

  lcd2.init();
  playerOneButton.init();
  playerTwoButton.init();
  menuButton.init();
  
  selectTimeControlOptionUiHandler.wire( &selectTimeControlUiHandler );
  currentUiHandler = &selectTimeControlUiHandler;

  //Serial.print( "mem:" );Serial.println( freeMemory() );
  //delay( 500 );
}

void loop() {
  currentUiHandler->tick( &clock );
  buzzer.tick();
  currentUiHandler->render( &clock );
}

