
#ifndef __FxFade_h__
#define __FxFade_h__

#include "PinEffect.h"

class FxFade : public PinEffect{
  
  uint32_t nextStepMilliseconds;
  uint16_t deltaMilliseconds;
  uint8_t value;
  bool increment;
  
public: 

  FxFade() {
  }

  virtual void tick(Clock *clock) {
    uint32_t currentTime = clock->currentTime();
    if( currentTime < nextStepMilliseconds ) {
      return;
    }
    if( value == 2 || value == 254 ) {
      increment = !increment;
    }
    value = increment ? value + 12 : value - 12;
    updateNextStepMilliseconds( currentTime );
  }
  
  virtual void apply(DigitalWritablePin *pin) {
  }
  
  virtual void apply(AnalogWritablePin *pin) {
    pin->set( value );
  }
  
  void setDelay(uint16_t delayMilliseconds, Clock *clock) {
    deltaMilliseconds = 4;//delayMilliseconds / 256;
    value = 2;
    increment = false;
    updateNextStepMilliseconds( clock->currentTime() );
  }
  
private:

  void updateNextStepMilliseconds(uint32_t currentTime) {
    nextStepMilliseconds = currentTime + deltaMilliseconds;
  }
  
};

#endif
