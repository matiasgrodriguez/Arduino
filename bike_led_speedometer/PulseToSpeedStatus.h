
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
    return pulseCounter->getCurrentPulseElapsedInterval( clock ) > pulseCounter->getMinusOnePulseInterval();
    /*
    if( pulseCounter->getMinusOnePulseInterval() > STOPPED_DELAY ) {
      status = AcceleratingOrConstant;
    } else if( pulseCounter->getMinusOnePulseInterval() <= minusTwoPulseInterval ) {
      status = AcceleratingOrConstant;
    } else {
      uint32_t delta = pulseCounter->getMinusOnePulseInterval() - minusTwoPulseInterval;
      //only consider decelerating if speed decreases more than 15%
      status = delta * 15 <= minusTwoPulseInterval ? AcceleratingOrConstant : Decelerating;
      //status = Decelerating;
    }
    */
  }
  
  Status getStatus() {
    return status;
  }
  
};

#endif 
