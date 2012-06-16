
#ifndef __Accelerometer_h__
#define __Accelerometer_h__

#include "PulsesPerSecondCounter.h"

class Accelerometer {

public:

  enum Status { None, Accelerating, Decelerating };

private:

  PulsesPerSecondCounter *pulseCounter;
  uint16_t pulseCount;
  Status status;
  
public:

  Accelerometer(PulsesPerSecondCounter *pulseCounter) {
    this->pulseCounter = pulseCounter;
    pulseCount = 0;
    status = None;
  }
  
  void tick(Clock *clock) {
    if( !pulseCounter->checkIfwasUpdatedAndClearFlag() ) {
      return;
    }
    uint16_t currentPulseCount = pulseCounter->getPulsesPerSecond();
    status = currentPulseCount == pulseCount ? None : ( currentPulseCount > pulseCount ? Accelerating : Decelerating ) ;
    pulseCount = currentPulseCount;
  }
  
  Status getStatus() {
    return status;
  }
  
};

#endif

