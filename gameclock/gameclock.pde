
#include "base.h"
#include "ManualClock.h"
#include "ArduinoClock.h"
#include "GameClock.h"

GameClock gameClock;
Clock *clock;

void setup() {
  Serial.begin(9600);

  //gameClock.setup();
  clock = new ManualClock();
  //clock = new ArduinoClock();  
}

void loop() {
  Serial.println( clock->currentTime() );
  //uint32_t currentTime = clock->currentTime();
  //Serial.println( currentTime );
  //manualClock.setCurrentTime( currentTime + 1 );
}

