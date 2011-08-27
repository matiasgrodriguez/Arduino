
#ifndef __ByoYomiTimeControlUi_h__
#define __ByoYomiTimeControlUi_h__

#include <avr/pgmspace.h>
#include "TimeControlUi.h"
#include "ByoYomiTimeControl.h"

const prog_char byoYomiName[] PROGMEM = "Byo Yomi";

const prog_char byoYomiOption1[] PROGMEM = "KGS MEDIUM           25m +5(30s)";
const prog_char byoYomiOption2[] PROGMEM = "KGS FAST             10m +5(20s)";
const prog_char byoYomiOption3[] PROGMEM = "KGS BLITZ             1m +3(10s)";

const prog_char *byoYomiOptions[] PROGMEM = {
  byoYomiOption1, byoYomiOption2, byoYomiOption3
};

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
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer1, uint8_t *buffer2) {
    formatTime( timeControl->getPlayerOneTime( clock ), &buffer1[  0 ] );
    formatTime( timeControl->getPlayerTwoTime( clock ), &buffer1[ 11 ] );
    
    ByoYomiTimeControl *byoTomi = (ByoYomiTimeControl*)timeControl;
    if( byoTomi->isPlayerOneInNormalTime() ) {
      buffer2[ 0 ]='n';
    }else {
      uint8_t numberBuffer[2];
      uint16_t remaining = byoTomi->getPlayerOneRemainingByoYomiPeriods();
      itoa( remaining, (char*)numberBuffer, 10 );
      uint16_t length = strlen( (char*)numberBuffer );
      memcpy( buffer2, numberBuffer, length );
    }

    if( byoTomi->isPlayerTwoInNormalTime() ) {
      buffer2[ 15 ]='n';
    }else {
      uint8_t numberBuffer[2];
      uint16_t remaining = byoTomi->getPlayerTwoRemainingByoYomiPeriods();
      Serial.println( remaining );
      itoa( remaining, (char*)numberBuffer, 10 );
      uint16_t length = strlen( (char*)numberBuffer );
      memcpy( &buffer2[16-length], numberBuffer, length );
    }
  }
  
};

#endif

