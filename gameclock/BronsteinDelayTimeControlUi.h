
#ifndef __BronsteinDelayTimeControlUi_h__
#define __BronsteinDelayTimeControlUi_h__

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "TimeControlUi.h"
#include "BronsteinDelayTimeControl.h"

const prog_char bronsteinDelayName[] PROGMEM = "Bronstein Delay";

const prog_uint8_t bronsteinDelayOption1[] PROGMEM = "                  2 min + 12 sec";
const prog_uint8_t bronsteinDelayOption2[] PROGMEM = "                  5 min + 12 sec";
const prog_uint8_t bronsteinDelayOption3[] PROGMEM = "                 10 min + 10 sec";

const prog_uint8_t *bronsteinDelayOptions[] PROGMEM = {
  bronsteinDelayOption1, bronsteinDelayOption2, bronsteinDelayOption3
};

const prog_char BRONSTEIN_FORMAT[] PROGMEM = "delay %d sec";

class BronsteinDelayTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_char *getName() {
    return bronsteinDelayName;
  }
  
  virtual int16_t getNumberOfOptions() {
    return 3;
  }
  
  virtual const prog_uint8_t *getOption(int16_t option) {
    return bronsteinDelayOptions[ option ];
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
        time = 1000L * 60L * 5L;
        delay = 1000L * 1L;
        break;
      case 2:
        time = 1000L * 60L * 10L;
        delay = 1000L * 10L;
        break;
    }
    return new BronsteinDelayTimeControl( time, delay );
  }
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer1, uint8_t *buffer2) {
    formatTime( timeControl->getPlayerOneTime( clock ), &buffer1[  0 ] );
    formatTime( timeControl->getPlayerTwoTime( clock ), &buffer1[ 11 ] );
    
    BronsteinDelayTimeControl *brownsteinDelay = ( BronsteinDelayTimeControl* )timeControl;
    char buffer[16];
    sprintf_P( buffer, BRONSTEIN_FORMAT, ( brownsteinDelay->getDelay() / 1000L ) );
    uint16_t length = strlen( buffer );
    memcpy( &buffer2[ ( 16 - length ) / 2 ], buffer, length ); //center on screen
  }
  
};

#endif

