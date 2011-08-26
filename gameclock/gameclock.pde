

#include <LiquidCrystal.h>
#include <MemoryFree.h>

#include "base.h"

#include "ManualClock.h"
#include "ArduinoClock.h"

#include "GameClock.h"
#include "PushButton.h"

#include "SelectTimeControlUiHandler.h"
#include "GameUiHandler.h"

#include "ByoYomiTimeControlUi.h"
#include "CanadianByoYomiTimeControlUi.h"
#include "FischerDelayTimeControlUi.h"
#include "BronsteinDelayTimeControlUi.h"
#include "HourGlassTimeControlUi.h"
#include "SuddenDeathTimeControlUi.h"
//#include "NormalDelayTimeControlUi.h"


//Hardware:
PushButton playerOneButton( 9 ), playerTwoButton( 8 );
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
SelectTimeControlUiHandler selectTimeControlUiHandler;
GameUiHandler gameUiHandler;
UiHandler *currentUiHandler;


void setup() {
  Serial.begin(9600);
  Serial.println( "-= BEGIN =-" );
  Serial.println( sizeof(GameClock) );
  Serial.println( sizeof(ByoYomiTimeControl) );
  Serial.println( sizeof(PushButton) );
  
  lcd.begin( 16, 2 );
    
  clock = new ArduinoClock();
  
  gameUiHandler.setTimeControlUi( timeControls[ 1 ] );
  currentUiHandler = &gameUiHandler;
  currentUiHandler = &selectTimeControlUiHandler;

  gameClock.setup( clock, timeControls[ 1 ]->create( 0 ) );

  pinMode( 8, INPUT );
  pinMode( 9, INPUT );
  Serial.print( "freeMemory=" );Serial.println(freeMemory());  
}

void loop() {
  currentUiHandler->tick( clock );
  currentUiHandler->render( clock );
  
  delay( 50 );
}

