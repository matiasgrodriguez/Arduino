
#ifndef __FxBlink_h__
#define __FxBlink_h__

#include "PinEffect.h"

extern Clock *clock;

#define FX_BLINK_BIT_UPDATE 31

template <int DELAY> class FxBlink : public PinEffect {
  
  uint32_t toggleTimeAndUpdateFlag;

public:

  FxBlink() {
    updateToggleTime();
  }

  virtual void tick(Clock *clock) {
    bool update = clock->currentTime() >= getToggleTime();
    if( update ) {
      updateToggleTime();
      BIT_SET( 1ul, toggleTimeAndUpdateFlag, FX_BLINK_BIT_UPDATE );
    } else {
      BIT_CLEAR( 1ul, toggleTimeAndUpdateFlag, FX_BLINK_BIT_UPDATE );
    }
  }
  
  virtual void apply(DigitalWritablePin *pin) {
    if( BIT_GET( 1ul, toggleTimeAndUpdateFlag, FX_BLINK_BIT_UPDATE ) != 0 ) {
      pin->toggle();
    }
  }
  
  virtual void apply(AnalogWritablePin *pin) {
  }

private:

  void updateToggleTime() {
    toggleTimeAndUpdateFlag = clock->currentTime() + DELAY;
  }
  
  uint32_t getToggleTime() {
    return  toggleTimeAndUpdateFlag & ( ~( 1ul << FX_BLINK_BIT_UPDATE ) );
  }

};

#endif
