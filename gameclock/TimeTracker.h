
#ifndef __TimeTracker_h__
#define __TimeTracker_h__

#include "Clock.h"

class TimeTracker {

public:

  void setTime(int32_t totalTime);
  void addTime(int32_t delta);
  
  int32_t getTime(Clock *clock);
  int32_t getLastConsumedTime();

};

#endif

