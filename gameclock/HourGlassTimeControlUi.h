
#ifndef __HourGlassTimeControlUi_h__
#define __HourGlassTimeControlUi_h__

#include <avr/pgmspace.h>
//#include <stdlib.h>
#include "GameClock.h"
#include "GameClockLcd.h"
#include "TimeControlUi.h"
#include "HourGlassTimeControl.h"

const prog_char hourGlassName[] PROGMEM = "Hour Glass";

const prog_char hourGlassOption1[] PROGMEM = "                          30 sec";
const prog_char hourGlassOption2[] PROGMEM = "                           1 min";
const prog_char hourGlassOption3[] PROGMEM = "                           2 min";
const prog_char hourGlassOption4[] PROGMEM = "                           5 min";
const prog_char hourGlassOption5[] PROGMEM = "                          10 min";

const prog_char *hourGlassOptions[] PROGMEM = {
  hourGlassOption1, hourGlassOption2, hourGlassOption3, hourGlassOption4, hourGlassOption5
};

const prog_char HOURGLASS_FORMAT[] PROGMEM = "%c %d sec";

class HourGlassTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_char *getName() {
    return hourGlassName;
  }
  
  virtual int16_t getNumberOfOptions() {
    return 5;
  }
  
  virtual const prog_char *getOption(int16_t option) {
    switch( option ) {
      case 0: return hourGlassOptions[ option ];
      case 1: return hourGlassOptions[ option ];
      case 2: return hourGlassOptions[ option ];
      case 3: return hourGlassOptions[ option ];
      case 4: return hourGlassOptions[ option ];
    }
    return hourGlassOptions[ 0 ];
  }
  
  virtual TimeControl *create(int16_t option) { 
    uint32_t time = 0;
    switch( option ) {
      case 0:
        time = 1000L * 30L;
        break;
      case 1:
        time = 1000L * 60L * 1L;
        break;
      case 2:
        time = 1000L * 60L * 2L;
        break;
      case 3:
        time = 1000L * 60L * 5L;
        break;
      case 4:
        time = 1000L * 60L * 10L;
        break;
    }
    return new HourGlassTimeControl( time );
  }
  
  virtual void renderGame(GameClock *gameClock, GameClockLcd *lcd) {
    HourGlassTimeControl *hourGlass = ( HourGlassTimeControl* )gameClock->getTimeControl();
    lcd->printTopLeftTime( hourGlass->getPlayerOneTime( gameClock->getClock() ) );
    lcd->printTopRightTime( hourGlass->getPlayerTwoTime( gameClock->getClock() ) );

    if( hourGlass->getLastTransferedTime() != 0 ) {
      lcd->sPrintBottomCenter( HOURGLASS_FORMAT, ( hourGlass->wasTimeTransferredFromPlayerOne() ? '>' : '<' ), ( hourGlass->getLastTransferedTime() / 1000L ) );
    }
  }
  
};

#endif

