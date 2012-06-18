
#ifndef __Accelerometer2_h__
#define __Accelerometer2_h__

#include "Clock.h"
#include "PulseCounter.h"

class Accelerometer2 {
  
public:
  
  enum Status { None, Accelerating, Decelerating, Stopped };

private:

  PulseCounter *pulseCounter;  
  uint32_t lastPulseCount;
  Status status;
  
public:

  Accelerometer2(PulseCounter *pulseCounter) {
    this->pulseCounter = pulseCounter;
    lastPulseCount = 0;
  }

  void tick(Clock *clock) {
    uint32_t currentPulseCount = pulseCounter->getPulseCount();
    uint32_t minusOnePulseInterval = pulseCounter->getMinusOnePulseInterval();

    if( lastPulseCount == currentPulseCount ) {
      if( pulseCounter->getCurrentPulseElapsedInterval( clock ) > minusOnePulseInterval ) {
        status = pulseCounter->getCurrentPulseElapsedInterval( clock ) > 3000 ? Stopped : Decelerating;
      }
      return;
    }
    
    lastPulseCount = currentPulseCount;
    uint32_t minusTwoPulseInterval = pulseCounter->getMinusTwoPulseInterval();
    if( minusOnePulseInterval == minusTwoPulseInterval ) {
      status = None;
    } else {
      status = minusOnePulseInterval < minusTwoPulseInterval ? Accelerating : Decelerating;
    }
  }
  
  Status getStatus() {
    return status;
  }
  
};

#endif 
