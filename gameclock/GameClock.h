
#ifndef __GameClock_h__
#define __GameClock_h__

#include "Clock.h"
#include "TimeControl.h"
#include "TimeTracker.h"

class GameClock {
  
  TimeControl *timeControl;
  TimeTracker playerOne, playerTwo;
  
public:
  
  void setup(Clock *clock, TimeControl *timeControl) {
    this->timeControl = timeControl;
    
    this->timeControl->setup( &playerOne, &playerTwo );
  }
  
  void selectPlayerOne() {
  }
  
  void selectPlayerTwo() {
  }
  
  void pause() {
  }
  
  void resume() {
  }
  
};

#endif

