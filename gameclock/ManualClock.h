
#ifndef __ManualClock_h__
#define __ManualClock_h__

#include "Clock.h"

class ManualClock : public Clock {

  uint32_t time;
  
public:

  ManualClock() : time( 0 ) {
  }

  ManualClock(uint32_t initialTime) : time( initialTime ) {
  }

  virtual ~ManualClock() {
  }

  virtual uint32_t currentTime() {
    return time;
  }
  
  void setCurrentTime(uint32_t newTime) {
    time = newTime;
  }

};

#endif
