
#include "base.h"
#include "ManualClock.h"
#include "ArduinoClock.h"
#include "GameClock.h"
#include "TimeControlTest.h"
#include "SuddenDeathTimeControl.h"
#include "HourGlassTimeControl.h"
#include "FischerDelayTimeControl.h"

GameClock gameClock;
ManualClock *clock;
TimeControlTest timeControl( 20, 30 );
SuddenDeathTimeControl suddenDeathTc( 20 );
HourGlassTimeControl hourGalssTc( 100 );
FischerDelayTimeControl fischerDelayTc( 100, 10 );

void setup() {
  Serial.begin(9600);

  //clock = new ArduinoClock();  
  clock = new ManualClock();
  gameClock.setup( clock, &hourGalssTc );

  gameClock.tick();  
  clock->setCurrentTime( 1 );
  gameClock.tick();
  gameClock.selectPlayerOne();
  gameClock.tick();
  clock->setCurrentTime( 5 );
  gameClock.tick();
  gameClock.selectPlayerTwo();
  gameClock.tick();
  clock->setCurrentTime( 10 );
  gameClock.tick();
  gameClock.selectPlayerOne();
  clock->setCurrentTime( 20 );
  gameClock.tick();
  gameClock.selectPlayerTwo();
  gameClock.tick();
  clock->setCurrentTime( 25 );
  gameClock.selectPlayerOne();
  gameClock.tick();
  clock->setCurrentTime( 30 );
  gameClock.tick();
  clock->setCurrentTime( 31 );
  gameClock.tick();
  clock->setCurrentTime( 32 );
  gameClock.tick();
  clock->setCurrentTime( 33 );
  gameClock.tick();
  gameClock.selectPlayerTwo();
  clock->setCurrentTime( 53 );
  gameClock.tick();
  gameClock.selectPlayerOne();
  clock->setCurrentTime( 54 );
  gameClock.tick();
}

void loop() {
  //Serial.println( clock->currentTime() );
  //uint32_t currentTime = clock->currentTime();
  //Serial.println( currentTime );
  //manualClock.setCurrentTime( currentTime + 1 );
}

