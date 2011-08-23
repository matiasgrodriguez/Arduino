
#ifndef __ByoYomiTimeControlUi_h__
#define __ByoYomiTimeControlUi_h__

#include <avr/pgmspace.h>
#include "TimeControlUi.h"
#include "ByoYomiTimeControl.h"

const prog_uint8_t byoYomiName[] PROGMEM = "        Byo Yomi";

const prog_uint8_t byoYomiOption1[] PROGMEM = "KGS MEDIUM           25m +5(30s)";
const prog_uint8_t byoYomiOption2[] PROGMEM = "KGS FAST             10m +5(20s)";
const prog_uint8_t byoYomiOption3[] PROGMEM = "KGS BLITZ             1m +3(10s)";

const prog_uint8_t *byoYomiOptions[] PROGMEM = {
  byoYomiOption1, byoYomiOption2, byoYomiOption3
};

class ByoYomiTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_uint8_t *getName() {
    return byoYomiName;
  }
  
  virtual int16_t getNumberOfOptions() { 
    return 3;
  }
  
  virtual const prog_uint8_t *getOption(int16_t option) {
    return byoYomiOptions[ option ];
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
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer, uint8_t *buffer2) {
    static bool flag = true;
    if( flag ) {
      Serial.print( "PlayerOneTime: " );Serial.println( ( long )timeControl->getPlayerOneTime( clock ) );
      Serial.print( "PlayerTwoTime: " );Serial.println( ( long )timeControl->getPlayerTwoTime( clock ) );
      flag = false;
    }
    formatTime( timeControl->getPlayerOneTime( clock ), &buffer[  0 ] );
    formatTime( timeControl->getPlayerTwoTime( clock ), &buffer[ 11 ] );
  }
  
};

#endif

