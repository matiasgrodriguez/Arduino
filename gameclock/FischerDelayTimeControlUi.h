
#ifndef __FischerDelayTimeControlUi_h__
#define __FischerDelayTimeControlUi_h__

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "TimeControlUi.h"
#include "FischerDelayTimeControl.h"

const prog_uint8_t fischerDelayName[] PROGMEM = "Fischer Delay";
const prog_uint8_t fischerDelayOption1[] PROGMEM = "Chess Cube        10 sec + 1 sec";
const prog_uint8_t fischerDelayOption2[] PROGMEM = "Chess Cube         1 min + 1 sec";
const prog_uint8_t fischerDelayOption3[] PROGMEM = "Chess Cube        2 min + 12 sec";
const prog_uint8_t fischerDelayOption4[] PROGMEM = "Chess Cube         3 min + 2 sec";
const prog_uint8_t fischerDelayOption5[] PROGMEM = "Chess Cube         5 min + 3 sec";
const prog_uint8_t fischerDelayOption6[] PROGMEM = "Chess Cube       25 min + 10 sec";

const prog_uint8_t *fischerDelayOptions[] PROGMEM = {
  fischerDelayOption1, fischerDelayOption2, fischerDelayOption3, fischerDelayOption4, fischerDelayOption5, fischerDelayOption6
};

const prog_char FISCHER_FORMAT[] PROGMEM = "+%d sec";

class FischerDelayTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_uint8_t *getName() {
    return fischerDelayName;
  }
  
  virtual int16_t getNumberOfOptions() {
    return 6;
  }
  
  virtual const prog_uint8_t *getOption(int16_t option) {
    return fischerDelayOptions[ option ];
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
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer1, uint8_t *buffer2) {
    formatTime( timeControl->getPlayerOneTime( clock ), &buffer1[  0 ] );
    formatTime( timeControl->getPlayerTwoTime( clock ), &buffer1[ 11 ] );
    
    FischerDelayTimeControl *fischerDelay = ( FischerDelayTimeControl* )timeControl;
    char buffer[16];
    sprintf_P( buffer, FISCHER_FORMAT, ( fischerDelay->getBonus() / 1000L ) );
    uint16_t length = strlen( buffer );
    memcpy( &buffer2[ ( 16 - length ) / 2 ], buffer, length ); //center on screen
  }

};

#endif
