
#ifndef __BronsteinDelayTimeControlUi_h__
#define __BronsteinDelayTimeControlUi_h__

#include <stdlib.h>
#include "TimeControlUi.h"
#include "BronsteinDelayTimeControl.h"

const char bronsteinDelayName[] PROGMEM = "Bronstein Delay";

const char bronsteinDelayOption1[] PROGMEM = "                  2 min + 12 sec";
const char bronsteinDelayOption2[] PROGMEM = "Objective         3 min + 12 sec";
const char bronsteinDelayOption3[] PROGMEM = "                  5 min + 12 sec";
const char bronsteinDelayOption4[] PROGMEM = "                 10 min + 10 sec";

const char * const bronsteinDelayOptions[] PROGMEM = {
  bronsteinDelayOption1, bronsteinDelayOption2, bronsteinDelayOption3, bronsteinDelayOption4
};

const char bronsteinDelayFormat[] PROGMEM = "delay %d sec";

class BronsteinDelayTimeControlUi : public TimeControlUi {
  
public:

  virtual const char *getName() {
    return bronsteinDelayName;
  }
  
  virtual int16_t getNumberOfOptions() {
    return 4;
  }
  
  virtual const char *getOption(int16_t option) {
    switch( option ) {
      case 0: return bronsteinDelayOptions[ option ];
      case 1: return bronsteinDelayOptions[ option ];
      case 2: return bronsteinDelayOptions[ option ];
      case 3: return bronsteinDelayOptions[ option ];
    }
    return bronsteinDelayOptions[ 0 ];
  }
  
  virtual TimeControl *create(int16_t option) { 
    uint32_t time = 0;
    uint32_t delay = 0;
    switch( option ) {
      case 0:
        time = 1000L * 60L * 2L;
        delay = 1000L * 12L;
        break;
      case 1:
        time = 1000L * 60L * 3L;
        delay = 1000L * 12L;
        break;
      case 2:
        time = 1000L * 60L * 5L;
        delay = 1000L * 1L;
        break;
      case 3:
        time = 1000L * 60L * 10L;
        delay = 1000L * 10L;
        break;
    }
    return new BronsteinDelayTimeControl( time, delay );
  }
  
  virtual void renderGame(GameClock *gameClock, GameClockLcd *lcd) {
    TimeControlUi::renderGame( gameClock, lcd );
    
    BronsteinDelayTimeControl *bronsteinDelay = ( BronsteinDelayTimeControl* )gameClock->getTimeControl();
    lcd->sPrintBottomCenter( bronsteinDelayFormat, bronsteinDelay->getDelay() / 1000L );
  }
  
};

#endif

