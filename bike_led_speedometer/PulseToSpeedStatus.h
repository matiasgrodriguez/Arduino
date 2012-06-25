
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
    const uint32_t STOPPED_DELAY = 4000;

    if( lastPulseCount == currentPulseCount ) {
      if( currentPulseCount == 0 ) {
        status = Stopped;
      } else { 
        uint32_t currentPulseElapsedInterval = pulseCounter->getCurrentPulseElapsedInterval( clock );
        if( currentPulseElapsedInterval > minusOnePulseInterval ) {
          status = currentPulseElapsedInterval > STOPPED_DELAY ? Stopped : Decelerating;
        }
      }
      return;
    }
    
    lastPulseCount = currentPulseCount;
    if( currentPulseCount == 1 ) {
      status = AcceleratingOrConstant;
      return;
    }
    
    uint32_t minusTwoPulseInterval = pulseCounter->getMinusTwoPulseInterval();
    if( minusOnePulseInterval > STOPPED_DELAY ) {
      status = AcceleratingOrConstant;
    } else if( minusOnePulseInterval <= minusTwoPulseInterval ) {
      status = AcceleratingOrConstant;
    } else {
      uint32_t delta = minusOnePulseInterval - minusTwoPulseInterval;
      //only consider decelerating if speed decreases more than 15%
      status = delta * 15 <= minusTwoPulseInterval ? AcceleratingOrConstant : Decelerating;
    }
  }
  
  Status getStatus() {
    return status;
  }
  
};

#endif 
