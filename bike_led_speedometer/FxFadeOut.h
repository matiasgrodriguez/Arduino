
#ifndef __FxFadeOut_h__
#define __FxFadeOut_h__

#include "PinEffect.h"

extern Clock *clock;

#define FX_FADE_OUT_BIT_UPDATE     7

template <int DELTA> class FxFadeOut : public PinEffect {
  
  uint32_t nextStepMilliseconds;
  uint8_t valueAndUpdateFlag;

public: 

  FxFadeOut() {
    set();
  }
  
  void set() {
    valueAndUpdateFlag = 255;
    updateNextStepMilliseconds();
  }

  virtual void tick(Clock *clock) {
    uint8_t value = getValue();
    if( clock->currentTime() < nextStepMilliseconds ) {
      BIT_CLEAR( (uint8_t)1, valueAndUpdateFlag, FX_FADE_OUT_BIT_UPDATE );
      return;
    }
    BIT_SET( (uint8_t)1, valueAndUpdateFlag, FX_FADE_OUT_BIT_UPDATE );
    if( value == 0 ) {
      return;
    }
    value -= 1;
    setValue( value );
    updateNextStepMilliseconds();
  }
  
  virtual void apply(DigitalWritablePin *pin) {
  }
  
  virtual void apply(AnalogWritablePin *pin) {
    if( BIT_GET( (uint8_t)1, valueAndUpdateFlag, FX_FADE_OUT_BIT_UPDATE ) ) {
      uint8_t val = getValue() << 1;
      pin->set( val );
    }
  }
  
private:

  void updateNextStepMilliseconds() {
    nextStepMilliseconds = clock->currentTime() + DELTA;
  }
  
  uint8_t getValue() {
    return valueAndUpdateFlag & ~( (uint8_t)1 << 7 );
  }
  
  void setValue(uint8_t val) {
    valueAndUpdateFlag = ( (uint8_t)0x01 << 7 ) & valueAndUpdateFlag | val;
  }
  
};

#endif
