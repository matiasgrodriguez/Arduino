
#ifndef __CanadianByoYomiTimeControlUi_h__
#define __CanadianByoYomiTimeControlUi_h__

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "TimeControlUi.h"
#include "ByoYomiTimeControl.h"

const prog_char canadianByoYomiName[] PROGMEM = "Canadian ByoYomi";

const prog_char canadianByoYomiOption1[] PROGMEM = "IGS Panda       1m +25mov in 15m";
const prog_char canadianByoYomiOption2[] PROGMEM = "IGS Panda       1m +25mov in 10m";
const prog_char canadianByoYomiOption3[] PROGMEM = "IGS Panda       1m +25mov in  7m";
const prog_char canadianByoYomiOption4[] PROGMEM = "IGS Panda       1m +25mov in  5m";

const prog_char *canadianByoYomiOptions[] PROGMEM = {
  canadianByoYomiOption1, canadianByoYomiOption2, canadianByoYomiOption3, canadianByoYomiOption4
};

class CanadianByoYomiTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_char *getName() {
    return canadianByoYomiName;
  }
  
  virtual int16_t getNumberOfOptions() { 
    return 4;
  }
  
  virtual const prog_char *getOption(int16_t option) {
    switch( option ) {
      case 0: return canadianByoYomiOptions[ option ];
      case 1: return canadianByoYomiOptions[ option ];
      case 2: return canadianByoYomiOptions[ option ];
      case 3: return canadianByoYomiOptions[ option ];
    }
    return canadianByoYomiOptions[ 0 ];
  }
  
  virtual TimeControl *create(int16_t option) {
    uint32_t time = 1000L * 60L * 1L;
    uint16_t numberOfPlays = 25;
    uint16_t numberOfPeriods = 1;
    ByoYomiSetup byoYomiSetup;  
    
    switch(option) {
      case 0: 
        byoYomiSetup.time = time;
        byoYomiSetup.numberOfPeriods = numberOfPeriods;
        byoYomiSetup.periods[ 0 ].numberOfPlays = numberOfPlays;
        byoYomiSetup.periods[ 0 ].time = 1000L * 60L * 15L;
        break;
      case 1: 
        byoYomiSetup.time = time;
        byoYomiSetup.numberOfPeriods = numberOfPeriods;
        byoYomiSetup.periods[ 0 ].numberOfPlays = numberOfPlays;
        byoYomiSetup.periods[ 0 ].time = 1000L * 60L * 10L;
        break;
      case 2: 
        byoYomiSetup.time = time;
        byoYomiSetup.numberOfPeriods = numberOfPeriods;
        byoYomiSetup.periods[ 0 ].numberOfPlays = numberOfPlays;
        byoYomiSetup.periods[ 0 ].time = 1000L * 60L * 7L;
        break;
      case 3: 
        byoYomiSetup.time = time;
        byoYomiSetup.numberOfPeriods = numberOfPeriods;
        byoYomiSetup.periods[ 0 ].numberOfPlays = numberOfPlays;
        byoYomiSetup.periods[ 0 ].time = 1000L * 60L * 5L;
        break;
    }

    return new ByoYomiTimeControl( byoYomiSetup );
  }
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer1, uint8_t *buffer2) {
    formatTime( timeControl->getPlayerOneTime( clock ), &buffer1[  0 ] );
    formatTime( timeControl->getPlayerTwoTime( clock ), &buffer1[ 11 ] );
    ByoYomiTimeControl *canadian = ( ByoYomiTimeControl* )timeControl;
    uint8_t numberBuffer[3];
    
    if( canadian->isPlayerOneInNormalTime() ) {
      buffer2[ 0 ]='n';
    }else {
      uint16_t remaining = canadian->getPlayerOneRemainingNumberOfPlays();
      itoa( remaining, (char*)numberBuffer, 10 );
      uint16_t length = strlen( (char*)numberBuffer );
      memcpy( buffer2, numberBuffer, length );
    }
    
    if( canadian->isPlayerTwoInNormalTime() ) {
      buffer2[ 15 ]='n';
    }else {
      uint16_t remaining = canadian->getPlayerTwoRemainingNumberOfPlays();
      itoa( remaining, (char*)numberBuffer, 10 );
      uint16_t length = strlen( (char*)numberBuffer );
      memcpy( &buffer2[16-length], numberBuffer, length );
    }
  }
  
};

#endif

