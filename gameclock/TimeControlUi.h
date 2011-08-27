
#ifndef __TimeControlUi_h__
#define __TimeControlUi_h__

#include <avr/pgmspace.h>

#include "GameClock.h"
#include "GameClockLcd.h"

#define UI_BUFFER_SIZE 32

class TimeControlUi {

public:

  virtual const prog_char *getName() = 0;
  virtual int16_t getNumberOfOptions() = 0;
  virtual const prog_char *getOption(int16_t option) = 0;
  virtual TimeControl *create(int16_t option) = 0;
  
  virtual void renderGame(GameClock *gameClock, GameClockLcd *lcd) {
    TimeControl *timeControl = gameClock->getTimeControl();
    lcd->printTopLeftTime( timeControl->getPlayerOneTime( gameClock->getClock() ) );
    lcd->printTopRightTime( timeControl->getPlayerTwoTime( gameClock->getClock() ) );
  }
  
};

#endif

