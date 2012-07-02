
#ifndef __PulseToSpeedStatus_h__
#define __PulseToSpeedStatus_h__

#include "Clock.h"
#include "PulseCounter.h"

extern PulseCounter *pulseCounter;

class PulseToSpeedStatus {
  
public:
  
  enum Status { AcceleratingOrConstant, Decelerating, Stopped };

private:

  uint32_t lastPulseCount;
  Status status;
  
public:

  PulseToSpeedStatus() {
    lastPulseCount = 0;
    status = Stopped;
  }

  void tick(Clock *clock) {    
    if( isStopping( clock ) ) {
      status = Stopped;
    } else if( isDecelerating( clock ) ) {
      status = Decelerating;
    } else {
      status = AcceleratingOrConstant;
    }
    
    lastPulseCount = pulseCounter->getPulseCount();
  }
  

  bool isStopping(Clock *clock) {
    return 
      pulseCounter->getPulseCount() == 0
      || ( pulseCounter->getCurrentPulseElapsedInterval( clock ) > 5000 );
  }

  bool isDecelerating(Clock *clock) {
    //fix if last != current, compare its time
    if( pulseCounter->getCurrentPulseElapsedInterval( clock ) > pulseCounter->getMinusOnePulseInterval() ) {
      return true;
    }
    if( pulseCounter->getMinusOnePulseInterval() > 5000 ) {
      return false;
    }
    bool decelerating = pulseCounter->getMinusOnePulseInterval() > pulseCounter->getMinusTwoPulseInterval();
    return decelerating && status != Stopped;
    /*
      uint32_t delta = pulseCounter->getMinusOnePulseInterval() - minusTwoPulseInterval;
      //only consider decelerating if speed decreases more than 15%
      status = delta * 15 <= minusTwoPulseInterval ? AcceleratingOrConstant : Decelerating;
    }
    */
  }
  
  Status getStatus() {
    return status;
  }
  
};

#endif 
