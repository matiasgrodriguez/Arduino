
#ifndef __FischerDelayTimeControlUi_h__
#define __FischerDelayTimeControlUi_h__

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "TimeControlUi.h"
#include "FischerDelayTimeControl.h"

const char fischerDelayName[] PROGMEM = "Fischer Delay";

const char fischerDelayOption1[] PROGMEM = "Chess Cube        10 sec + 1 sec";
const char fischerDelayOption2[] PROGMEM = "Chess Cube         1 min + 1 sec";
const char fischerDelayOption3[] PROGMEM = "Chess Cube        2 min + 12 sec";
const char fischerDelayOption4[] PROGMEM = "Chess Cube         3 min + 2 sec";
const char fischerDelayOption5[] PROGMEM = "Chess Cube         5 min + 3 sec";
const char fischerDelayOption6[] PROGMEM = "Chess Cube       25 min + 10 sec";

const char * const fischerDelayOptions[] PROGMEM = {
  fischerDelayOption1, fischerDelayOption2, fischerDelayOption3, fischerDelayOption4, fischerDelayOption5, fischerDelayOption6
};

const char fischerDelayFormat[] PROGMEM = "+%d sec";

class FischerDelayTimeControlUi : public TimeControlUi {
  
public:

  virtual const char *getName() {
    return fischerDelayName;
  }
  
  virtual int16_t getNumberOfOptions() {
    return 6;
  }
  
  virtual const char *getOption(int16_t option) {
    switch( option ) {
      case 0: return fischerDelayOptions[ option ];
      case 1: return fischerDelayOptions[ option ];
      case 2: return fischerDelayOptions[ option ];
      case 3: return fischerDelayOptions[ option ];
      case 4: return fischerDelayOptions[ option ];
      case 5: return fischerDelayOptions[ option ];
    }
    return fischerDelayOptions[ 0 ];
  }
  
  virtual TimeControl *create(int16_t option) { 
    uint32_t time = 0;
    uint32_t bonus = 0;
    switch( option ) {
      case 0:
        time = 1000L * 10L;
        bonus = 1000L * 1L;
        break;
      case 1:
        time = 1000L * 60L;
        bonus = 1000L * 1L;
        break;
      case 2:
        time = 1000L * 60L * 2L;
        bonus = 1000L * 12L;
        break;
      case 3:
        time = 1000L * 60L * 3L;
        bonus = 1000L * 2L;
        break;
      case 4:
        time = 1000L * 60L * 5L;
        bonus = 1000L * 3L;
        break;
      case 5:
        time = 1000L * 60L * 25L;
        bonus = 1000L * 10L;
        break;
    }
    return new FischerDelayTimeControl( time, bonus );
  }
  
  virtual void renderGame(GameClock *gameClock, GameClockLcd *lcd) {
    TimeControlUi::renderGame( gameClock, lcd );
    
    FischerDelayTimeControl *fischerDelay = ( FischerDelayTimeControl* )gameClock->getTimeControl();    
    lcd->sPrintBottomCenter( fischerDelayFormat, fischerDelay->getBonus() / 1000L );
  }

};

#endif
