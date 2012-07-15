
#ifndef __PulseToSpeedStatus_h__
#define __PulseToSpeedStatus_h__

#include "Clock.h"
#include "PulseCounter.h"

extern PulseCounter *pulseCounter;

#define PULSE_TO_SPEED_STATUS_BIT_PULSED     31

class PulseToSpeedStatus {

public:
  
  enum Status { AcceleratingOrConstant, Decelerating, Stopped };

private:

  uint32_t lastPulseCountAndPulsedFlag;
  Status status;
  
public:

  PulseToSpeedStatus() {
    lastPulseCountAndPulsedFlag = 0;
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

    updateLastPulseCount( pulseCounter->getPulseCount() );
  }
    
  Status getStatus() {
    return status;
  }
  
  bool pulsedAndClearFlag() {
    return checkIfWasPulsedAndClearFlag();
  }
  
private:

  bool isStopping(Clock *clock) {
    return 
      pulseCounter->getPulseCount() == 0
      || ( pulseCounter->getCurrentPulseElapsedInterval( clock ) > 3000 );
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
  
  void updateLastPulseCount(uint32_t pulseCount) { 
    if( pulseCount == getLastPulseCount() ) {
      BIT_CLEAR( 1ul, lastPulseCountAndPulsedFlag, PULSE_TO_SPEED_STATUS_BIT_PULSED );
      return;
    }
    lastPulseCountAndPulsedFlag = pulseCount;
    BIT_SET( 1ul, lastPulseCountAndPulsedFlag, PULSE_TO_SPEED_STATUS_BIT_PULSED );
  }

  uint32_t getLastPulseCount() {
    return lastPulseCountAndPulsedFlag & ~( 1ul << PULSE_TO_SPEED_STATUS_BIT_PULSED );
  }
  
  bool checkIfWasPulsedAndClearFlag() {
    bool pulsed = BIT_GET( 1ul, lastPulseCountAndPulsedFlag, PULSE_TO_SPEED_STATUS_BIT_PULSED );
    if( pulsed ) {
      BIT_CLEAR( 1ul, lastPulseCountAndPulsedFlag, PULSE_TO_SPEED_STATUS_BIT_PULSED );
    }
    return pulsed;
  }
  
};

#endif 
