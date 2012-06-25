
#ifndef __PulseCounter_h__
#define __PulseCounter_h__

#include "Clock.h"
#include "DigitalPin.h"

class PulseCounter {
  
  DigitalPin *pulsePin;
  uint32_t pulseCount;
  
  uint32_t minusTwoPulseInterval;
  uint32_t minusOnePulseTime;
  uint32_t minusOnePulseInterval;

  bool pinState;
  
public:

  PulseCounter(DigitalPin *pulsePin) {
    this->pulsePin = pulsePin;
    pulseCount = 0;
    minusTwoPulseInterval = 0;
    minusOnePulseTime = 0;
    minusOnePulseInterval = 0;
    pinState = false;
  }

  void tick(Clock *clock) {
    bool currentPinState = pulsePin->isSet();
    if( pinStateDidntChange( currentPinState ) ) {
      return;
    }
    
    pinState = currentPinState;
    if( isPinOff() ) {
      return;
    }
    
    pulseCount++;
    
    minusTwoPulseInterval = minusOnePulseInterval;
    
    minusOnePulseInterval = clock->currentTime() - minusOnePulseTime;
    minusOnePulseTime = clock->currentTime();
  }
  
  uint32_t getPulseCount() {
    return pulseCount;
  }

  uint32_t getMinusTwoPulseInterval() {
    return minusTwoPulseInterval;
  }

  uint32_t getMinusOnePulseTime() {
    return minusOnePulseTime;
  }

  uint32_t getMinusOnePulseInterval() {
    return minusOnePulseInterval;
  }
  
  uint32_t getCurrentPulseElapsedInterval(Clock *clock) {
    return clock->currentTime() - minusOnePulseTime;
  }
    
private:

  bool pinStateDidntChange(bool currentPinState) {
    return pinState == currentPinState;
  }
  
  bool isPinOff() {
    return pinState == false;
  }

};

#endif

