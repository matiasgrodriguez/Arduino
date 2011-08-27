
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
Clock *clock;
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
  Serial.println( "-= :) =-" );
  Serial.println( sizeof(GameClock) );
  Serial.println( sizeof(ByoYomiTimeControl) );
  Serial.println( sizeof(PushButton) );

  lcd2.init();
  playerOneButton.init();
  playerTwoButton.init();
  okButton.init();
  backButton.init();

  clock = new ArduinoClock();
  
  selectTimeControlOptionUiHandler.wire( &selectTimeControlUiHandler );
  currentUiHandler = &selectTimeControlUiHandler;

  Serial.print( "freeMem=" );Serial.println(freeMemory());  
}

void loop() {
  currentUiHandler->tick( clock );
  currentUiHandler->render( clock );
  
  delay( 50 );
}

