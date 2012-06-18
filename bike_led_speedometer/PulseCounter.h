
#ifndef __PulseCounter_h__
#define __PulseCounter_h__

#include "Clock.h"
#include "DigitalPin.h"

class PulseCounter {
  
  DigitalPin *pulsePin;
  uint32_t pulseCount;
  
  uint32_t minusTwoPulseTime;
  uint16_t minusTwoPulseInterval;
  uint32_t minusOnePulseTime;
  uint16_t minusOnePulseInterval;

  bool pinState;
  
public:

  PulseCounter(DigitalPin *pulsePin) {
    this->pulsePin = pulsePin;
    pulseCount = 0;
    minusTwoPulseTime = 0;
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
    
    uint32_t currentTime = clock->currentTime();
    pulseCount++;
    
    minusTwoPulseTime = minusOnePulseTime;
    minusTwoPulseInterval = minusOnePulseInterval;
    
    minusOnePulseInterval = currentTime - minusOnePulseTime;
    minusOnePulseTime = currentTime;
  }
  
  uint32_t getPulseCount() {
    return pulseCount;
  }

  uint32_t getMinusTwoPulseTime() {
    return minusTwoPulseTime;
  }

  uint16_t getMinusTwoPulseInterval() {
    return minusTwoPulseInterval;
  }

  uint32_t getMinusOnePulseTime() {
    return minusOnePulseTime;
  }

  uint16_t getMinusOnePulseInterval() {
    return minusOnePulseInterval;
  }
  
  uint16_t getCurrentPulseElapsedInterval(Clock *clock) {
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

