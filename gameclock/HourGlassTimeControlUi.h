
#ifndef __HourGlassTimeControlUi_h__
#define __HourGlassTimeControlUi_h__

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "TimeControlUi.h"
#include "HourGlassTimeControl.h"

const prog_char hourGlassName[] PROGMEM = "Hour Glass";

const prog_uint8_t hourGlassOption1[] PROGMEM = "                          30 sec";
const prog_uint8_t hourGlassOption2[] PROGMEM = "                           1 min";
const prog_uint8_t hourGlassOption3[] PROGMEM = "                           2 min";
const prog_uint8_t hourGlassOption4[] PROGMEM = "                           5 min";
const prog_uint8_t hourGlassOption5[] PROGMEM = "                          10 min";

const prog_uint8_t *hourGlassOptions[] PROGMEM = {
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
  
  virtual const prog_uint8_t *getOption(int16_t option) {
    return hourGlassOptions[ option ];
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
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer1, uint8_t *buffer2) {
    formatTime( timeControl->getPlayerOneTime( clock ), &buffer1[  0 ] );
    formatTime( timeControl->getPlayerTwoTime( clock ), &buffer1[ 11 ] );
    
    HourGlassTimeControl *hourGlass = ( HourGlassTimeControl* )timeControl;
    if( hourGlass->getLastTransferedTime() != 0 ) {
      char buffer[16];
      sprintf_P( buffer, HOURGLASS_FORMAT, ( hourGlass->wasTimeTransferredFromPlayerOne() ? '>' : '<' ), ( hourGlass->getLastTransferedTime() / 1000L ) );
      uint16_t length = strlen( buffer );
      memcpy( &buffer2[ ( 16 - length ) / 2 ], buffer, length ); //center on screen
    }
  }
  
};

#endif

