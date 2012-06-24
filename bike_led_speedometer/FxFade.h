
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
    if( value == 0 || value == 255 ) {
      increment = !increment;
    }
    value = increment ? value + 1 : value - 1;
    updateNextStepMilliseconds( currentTime );
  }
  
  virtual void apply(DigitalWritablePin *pin) {
  }
  
  virtual void apply(AnalogWritablePin *pin) {
    pin->set( value );
  }
  
  void setDelay(uint16_t delayMilliseconds, Clock *clock) {
    deltaMilliseconds = delayMilliseconds / 256;
    value = 0;
    increment = false;
    updateNextStepMilliseconds( clock->currentTime() );
  }
  
private:

  void updateNextStepMilliseconds(uint32_t currentTime) {
    nextStepMilliseconds = currentTime + deltaMilliseconds;
  }
  
};

#endif
