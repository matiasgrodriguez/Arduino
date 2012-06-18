
#ifndef __PulseToSpeedStatus_h__
#define __PulseToSpeedStatus_h__

#include "Clock.h"
#include "PulseCounter.h"

class PulseToSpeedStatus {
  
public:
  
  enum Status { AcceleratingOrConstant, Decelerating, Stopped };

private:

  PulseCounter *pulseCounter;
  uint32_t lastPulseCount;
  Status status;
  
public:

  PulseToSpeedStatus(PulseCounter *pulseCounter) {
    this->pulseCounter = pulseCounter;
    lastPulseCount = 0;
  }

  void tick(Clock *clock) {
    uint32_t currentPulseCount = pulseCounter->getPulseCount();
    uint32_t minusOnePulseInterval = pulseCounter->getMinusOnePulseInterval();

    if( lastPulseCount == currentPulseCount ) {
      if( pulseCounter->getCurrentPulseElapsedInterval( clock ) > minusOnePulseInterval ) {
        status = pulseCounter->getCurrentPulseElapsedInterval( clock ) > 4000 ? Stopped : Decelerating;
      }
      return;
    }
    
    lastPulseCount = currentPulseCount;
    uint32_t minusTwoPulseInterval = pulseCounter->getMinusTwoPulseInterval();
    status = minusOnePulseInterval <= minusTwoPulseInterval ? AcceleratingOrConstant : Decelerating;
    //TODO: Use a threshold so a small speed decrease does not return Decelerating.
  }
  
  Status getStatus() {
    return status;
  }
  
};

#endif 
