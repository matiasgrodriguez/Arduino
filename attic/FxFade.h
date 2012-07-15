
#ifndef __FxFade_h__
#define __FxFade_h__

#include "PinEffect.h"

extern Clock *clock;

#define FX_FADE_BIT_UPDATE     7
#define FX_FADE_BIT_INCREMENT  6

template <int DELTA> class FxFade : public PinEffect{
  
  uint32_t nextStepMilliseconds;
  uint8_t valueIncrementAndFlag;

public: 

  FxFade() {
    valueIncrementAndFlag = 0;
    updateNextStepMilliseconds();
  }

  virtual void tick(Clock *clock) {
    if( clock->currentTime() < nextStepMilliseconds ) {
      BIT_CLEAR( (uint8_t)1, valueIncrementAndFlag, FX_FADE_BIT_UPDATE );
      return;
    }
    BIT_SET( (uint8_t)1, valueIncrementAndFlag, FX_FADE_BIT_UPDATE );
    uint8_t value = getValue();
    if( value == 0 || value == 63 ) {
      BIT_TOGGLE( (uint8_t)1, valueIncrementAndFlag, FX_FADE_BIT_INCREMENT );
    }
    bool increment = BIT_GET( (uint8_t)1, valueIncrementAndFlag, FX_FADE_BIT_INCREMENT );
    value += increment ? 1 : -1;
    setValue( value );
    updateNextStepMilliseconds();
  }
  
  virtual void apply(DigitalWritablePin *pin) {
  }
  
  virtual void apply(AnalogWritablePin *pin) {
    if( BIT_GET( (uint8_t)1, valueIncrementAndFlag, FX_FADE_BIT_UPDATE ) ) {
      uint8_t val = getValue();
      pin->set( val << 2 );//*4
    }
  }
  
private:

  void updateNextStepMilliseconds() {
    nextStepMilliseconds = clock->currentTime() + DELTA;
  }
  
  uint8_t getValue() {
    return valueIncrementAndFlag & ~( (uint8_t)0x03 << 6 );
  }
  
  void setValue(uint8_t val) {
    valueIncrementAndFlag = ( (uint8_t)0x03 << 6 ) & valueIncrementAndFlag | val;
  }
  
};

#endif
