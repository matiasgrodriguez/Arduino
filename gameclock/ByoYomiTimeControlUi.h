
#ifndef __ByoYomiTimeControlUi_h__
#define __ByoYomiTimeControlUi_h__

#include <avr/pgmspace.h>
#include "TimeControlUi.h"
#include "ByoYomiTimeControl.h"

const prog_char byoYomiName[] PROGMEM = "Byo Yomi";

const prog_char byoYomiOption1[] PROGMEM = "KGS Medium           25m +5(30s)";
const prog_char byoYomiOption2[] PROGMEM = "KGS Fast             10m +5(20s)";
const prog_char byoYomiOption3[] PROGMEM = "KGS Blitz             1m +3(10s)";

const prog_char *byoYomiOptions[] PROGMEM = {
  byoYomiOption1, byoYomiOption2, byoYomiOption3
};

const prog_char byoYomiUiNormalTime[] PROGMEM = "normal";
const prog_char byoYomiUiFormat[] PROGMEM = "%d";

class ByoYomiTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_char *getName() {
    return byoYomiName;
  }
  
  virtual int16_t getNumberOfOptions() { 
    return 3;
  }
  
  virtual const prog_char *getOption(int16_t option) {
    switch( option ) {
      case 0: return byoYomiOptions[ option ];
      case 1: return byoYomiOptions[ option ];
      case 2: return byoYomiOptions[ option ];
    }
    return byoYomiOptions[ 0 ];
  }
  
  virtual TimeControl *create(int16_t option) {
    uint32_t byoYomiTime;
    ByoYomiSetup byoYomiSetup;  
    
    switch(option) {
      case 0: 
        byoYomiSetup.time = 1000L * 60L * 25L;
        byoYomiSetup.numberOfPeriods = 5;
        byoYomiTime = 30L * 1000L;
        byoYomiSetup.periods[ 0 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 0 ].time = byoYomiTime;
        byoYomiSetup.periods[ 1 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 1 ].time = byoYomiTime;
        byoYomiSetup.periods[ 2 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 2 ].time = byoYomiTime;
        byoYomiSetup.periods[ 3 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 3 ].time = byoYomiTime;
        byoYomiSetup.periods[ 4 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 4 ].time = byoYomiTime;
        break;
      case 1: 
        byoYomiSetup.time = 1000L * 60L * 10L;
        byoYomiSetup.numberOfPeriods = 5;
        byoYomiTime = 20L * 1000L;
        byoYomiSetup.periods[ 0 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 0 ].time = byoYomiTime;
        byoYomiSetup.periods[ 1 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 1 ].time = byoYomiTime;
        byoYomiSetup.periods[ 2 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 2 ].time = byoYomiTime;
        byoYomiSetup.periods[ 3 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 3 ].time = byoYomiTime;
        byoYomiSetup.periods[ 4 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 4 ].time = byoYomiTime;
        break;
      case 2: 
        byoYomiSetup.time = 1000L * 60L * 1L;
        byoYomiSetup.numberOfPeriods = 3;
        byoYomiTime = 10L * 1000L;
        byoYomiSetup.periods[ 0 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 0 ].time = byoYomiTime;
        byoYomiSetup.periods[ 1 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 1 ].time = byoYomiTime;
        byoYomiSetup.periods[ 2 ].numberOfPlays = 1;
        byoYomiSetup.periods[ 2 ].time = byoYomiTime;
        break;
    }

    return new ByoYomiTimeControl( byoYomiSetup );
  }
  
  virtual void renderGame(GameClock *gameClock, GameClockLcd *lcd) {
    ByoYomiTimeControl *byoYomi = ( ByoYomiTimeControl* )gameClock->getTimeControl();
    lcd->printTopLeftTime( byoYomi->getPlayerOneTime( gameClock->getClock() ) );
    lcd->printTopRightTime( byoYomi->getPlayerTwoTime( gameClock->getClock() ) );
    
    if( byoYomi->isPlayerOneInNormalTime() ) {
      lcd->printBottomLeft( byoYomiUiNormalTime );
    }else {
      lcd->sPrintBottomLeft( byoYomiUiFormat, byoYomi->getPlayerOneRemainingByoYomiPeriods() );
    }

    if( byoYomi->isPlayerTwoInNormalTime() ) {
      lcd->printBottomRight( byoYomiUiNormalTime );
    }else {
      lcd->sPrintBottomRight( byoYomiUiFormat, byoYomi->getPlayerTwoRemainingByoYomiPeriods() );
    }
  }
  
};

#endif

