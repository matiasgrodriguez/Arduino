
#ifndef __BikeLedSpeedometerUi_h__
#define __BikeLedSpeedometerUi_h__

#include "AnalogWritablePin.h"
#include "PulseToSpeedStatus.h"
#include "FxFadeOut.h"
#include "FxBlink.h"

extern AnalogWritablePin *pulseFeedbackPin;
extern DigitalWritablePin *deceleratingPin;
extern PulseToSpeedStatus *pulseToSpeedStatus;

extern void watchdog();

class BikeLedSpeedometerUi {
  
  FxFadeOut<4> fxFadeOut;
  FxBlink<150> fxBlink;
  
public:

  BikeLedSpeedometerUi(Clock *clock) : fxBlink() {
  }

  void tick(Clock *clock) {    
    PulseToSpeedStatus::Status status = pulseToSpeedStatus->getStatus();
    fxBlink.tick( clock );
    fxFadeOut.tick( clock );
    
    if( status == PulseToSpeedStatus::AcceleratingOrConstant ) {
      updateAcceleratingOrConstant();
    } else if( status == PulseToSpeedStatus::Decelerating ) {
      updateDecelerating();
    } else if ( status == PulseToSpeedStatus::Stopped ) {
      updateStoped();
    }

    if( pulseToSpeedStatus->pulsedAndClearFlag() ) {
      fxFadeOut.set();
    }
    fxFadeOut.apply( pulseFeedbackPin );

    watchdog();
  }
  
private:

  void updateAcceleratingOrConstant() {
    deceleratingPin->set( false );
  }

  void updateDecelerating() {
    deceleratingPin->set( true );
  }

  void updateStoped() {
    fxBlink.apply( deceleratingPin );
  }

};

#endif

