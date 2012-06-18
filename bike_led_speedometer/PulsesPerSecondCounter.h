
#ifndef __PulsesPerSecondCounter_h__
#define __PulsesPerSecondCounter_h__

#include "Clock.h"
#include "DigitalPin.h"

class PulsesPerSecondCounter {
  
  DigitalPin *pin;
  uint32_t pulsesPerSecondUpdateTime;
  uint16_t pulseCount;
  uint16_t pulsesPerSecond;
  bool state;
  bool pulsesPerSecondUpdated;

public:

  PulsesPerSecondCounter(DigitalPin *pin) {
    this->pin = pin;
    pulsesPerSecondUpdateTime = 0;
    pulseCount = 0;
    pulsesPerSecond = 0;
    state = false;
    pulsesPerSecondUpdated = false;
  }

  virtual void tick(Clock *clock) {
    updatePulseCount();
    updatePulsesPerSecond( clock );
  }
  
  uint32_t getPulsesPerSecond() {
    return pulsesPerSecond;
  }
  
  bool checkIfwasUpdatedAndClearFlag() {
    if( pulsesPerSecondUpdated ) {
      pulsesPerSecondUpdated = false;
      return true;
    }
    return false;
  }
  
private:

  void updatePulseCount() {
    bool pinState = pin->isSet();
    if( stateDidntChange( pinState ) ) {
      return;
    }
    state = pinState;
    if( state ) {
      pulseCount++;
    }
  }

  bool stateDidntChange(bool currentPinState) {
    return state == currentPinState;
  }
  
  void updatePulsesPerSecond(Clock *clock) {
    const uint32_t delta = 1000;
    uint32_t currentTime = clock->currentTime();
    if( currentTime - pulsesPerSecondUpdateTime < delta ) {
      return;
    }
    pulsesPerSecond = pulseCount;
    pulsesPerSecondUpdateTime = currentTime;
    pulseCount = 0;
    pulsesPerSecondUpdated = true;
  }

};

#endif
