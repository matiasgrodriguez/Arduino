
#ifndef __TimeTracker_h__
#define __TimeTracker_h__

#include "Clock.h"

class TimeTracker {

public:

  virtual void setTime(int32_t totalTime) = 0;
  virtual void addTime(int32_t delta) = 0;
  
  virtual int32_t getTime(Clock *clock) = 0;
  virtual int32_t getLastConsumedTime() = 0;

};

#endif

