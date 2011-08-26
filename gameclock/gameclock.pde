

#include <LiquidCrystal.h>
#include <MemoryFree.h>

#include "base.h"
#include "ManualClock.h"
#include "ArduinoClock.h"
#include "GameClock.h"
#include "SuddenDeathTimeControl.h"
#include "HourGlassTimeControl.h"
#include "FischerDelayTimeControl.h"
#include "ByoYomiTimeControl.h"
#include "BronsteinDelayTimeControl.h"
#include "SimpleDelayTimeControl.h"
#include "PushButton.h"
#include "GameUiHandler.h"

#include "TimeControlUi.h"
#include "ByoYomiTimeControlUi.h"
#include "CanadianByoYomiTimeControlUi.h"
#include "FischerDelayTimeControlUi.h"
#include "BronsteinDelayTimeControlUi.h"
#include "HourGlassTimeControlUi.h"
#include "SuddenDeathTimeControlUi.h"


//Hardware:
PushButton playerOneButton( 9 ), playerTwoButton( 8 );
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//GameClock...
GameClock gameClock;
Clock *clock;
TimeControl *timeControl;

//TimeControls:
TimeControlUi *timeControls[] = {
  new SuddenDeathTimeControlUi(),
  new HourGlassTimeControlUi(),
  new ByoYomiTimeControlUi(),
  new CanadianByoYomiTimeControlUi(),
  new FischerDelayTimeControlUi(),
  new BronsteinDelayTimeControlUi()
};

//User Interface ...
TimeControlUi *timeControlUi;
UiHandler *currentUiHandler;


void setup() {
  Serial.begin(9600);
  Serial.println( "-= BEGIN =-" );
  Serial.println( sizeof(GameClock) );
  Serial.println( sizeof(ByoYomiTimeControl) );
  Serial.println( sizeof(PushButton) );
  
  lcd.begin( 16, 2 );
  
  //timeControlUi = new ByoYomiTimeControlUi();
  //timeControlUi = new CanadianByoYomiTimeControlUi();
  //timeControlUi = new FischerDelayTimeControlUi();
  //timeControlUi = new BronsteinDelayTimeControlUi();
  //timeControlUi = new HourGlassTimeControlUi();
  timeControlUi = new SuddenDeathTimeControlUi();
  
  clock = new ArduinoClock();
  timeControl = timeControlUi->create( 6 );
  currentUiHandler = new GameUiHandler();

  gameClock.setup( clock, timeControl );

  pinMode( 8, INPUT );
  pinMode( 9, INPUT );
  Serial.print( "freeMemory=" );Serial.println(freeMemory());  
}

void loop() {
  currentUiHandler->tick( clock );
  currentUiHandler->render();
  
  delay( 50 );
}

