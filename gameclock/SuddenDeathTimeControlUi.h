
#ifndef __SuddenDeathTimeControlUi_h__
#define __SuddenDeathTimeControlUi_h__

#include <avr/pgmspace.h>
#include <stdlib.h>

#include "TimeControlUi.h"
#include "SuddenDeathTimeControl.h"

const prog_char suddenDeathName[] PROGMEM = "Sudden Death";

const prog_char suddenDeathOption1[] PROGMEM = "                          30 sec";
const prog_char suddenDeathOption2[] PROGMEM = "                           1 min";
const prog_char suddenDeathOption3[] PROGMEM = "                           5 min";
const prog_char suddenDeathOption4[] PROGMEM = "                          10 min";
const prog_char suddenDeathOption5[] PROGMEM = "                          20 min";
const prog_char suddenDeathOption6[] PROGMEM = "                          30 min";
const prog_char suddenDeathOption7[] PROGMEM = "                          1 hour";

const prog_char *suddenDeathOptions[] PROGMEM = {
  suddenDeathOption1, suddenDeathOption2, suddenDeathOption3, suddenDeathOption4, suddenDeathOption5, suddenDeathOption6, suddenDeathOption7
};

class SuddenDeathTimeControlUi : public TimeControlUi {
  
public:

  virtual const prog_char *getName() {
    return suddenDeathName;
  }
  
  virtual int16_t getNumberOfOptions() {
    return 7;
  }
  
  virtual const prog_char *getOption(int16_t option) {
    switch( option ) {
      case 0: return suddenDeathOptions[ option ];
      case 1: return suddenDeathOptions[ option ];
      case 2: return suddenDeathOptions[ option ];
      case 3: return suddenDeathOptions[ option ];
      case 4: return suddenDeathOptions[ option ];
      case 5: return suddenDeathOptions[ option ];
      case 6: return suddenDeathOptions[ option ];
    }
    return suddenDeathOptions[ 0 ];

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
        time = 1000L * 60L * 5L;
        break;
      case 3:
        time = 1000L * 60L * 10L;
        break;
      case 4:
        time = 1000L * 60L * 20L;
        break;
      case 5:
        time = 1000L * 60L * 30L;
        break;
      case 6:
        time = 1000L * 60L * 60L * 1L;
        break;
    }
    return new SuddenDeathTimeControl( time );
  }

};

#endif

