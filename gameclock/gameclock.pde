

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

GameClock gameClock;
Clock *clock;
TimeControl *timeControl;
TimeControlUi *timeControlUi;
PushButton playerOneButton( 9 );
PushButton playerTwoButton( 8 );
UiHandler *currentUiHandler;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void printTime() {
  uint8_t buffer[ 16 ];
  for(int i = 0; i < 16; ++i) {
    buffer[ i ] = ' ';
  }
  
  timeControlUi->render( clock, timeControl, buffer );
  //lcd.clear();
  lcd.setCursor( 0, 0 );
  lcd.print( (const char*)buffer );
  lcd.setCursor( 0, 1 );
  
  memcpy_P( buffer, timeControlUi->getName(), 16 );
  lcd.print( (const char*)buffer );
}

void setup() {
  Serial.begin(9600);
  Serial.println( "-= BEGIN =-" );
  Serial.println( sizeof(GameClock) );
  Serial.println( sizeof(ByoYomiTimeControl) );
  Serial.println( sizeof(PushButton) );
  
  lcd.begin( 16, 2 );
  
  timeControlUi = new ByoYomiTimeControlUi();
  clock = new ArduinoClock();
  timeControl = timeControlUi->create( 2 );
  currentUiHandler = new GameUiHandler();

  gameClock.setup( clock, timeControl );

  pinMode( 8, INPUT );
  pinMode( 9, INPUT );
  Serial.print( "freeMemory=" );Serial.println(freeMemory());  
}

void loop() {
  currentUiHandler->tick( clock );
  printTime();
  
  delay( 50 );
}

