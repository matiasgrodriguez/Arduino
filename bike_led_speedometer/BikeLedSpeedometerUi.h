
#ifndef __BikeLedSpeedometerUi_h__
#define __BikeLedSpeedometerUi_h__

#include "AnalogWritablePin.h"
#include "PulseToSpeedStatus.h"
#include "FxFade.h"
#include "FxBlink.h"

extern AnalogWritablePin *acceleratingPin;
extern DigitalWritablePin *deceleratingPin;
extern PulseToSpeedStatus *pulseToSpeedStatus;

extern void watchdog();

class BikeLedSpeedometerUi {
  
  FxFade<1> fxFade;
  FxBlink<150> fxBlink;
  
public:

  BikeLedSpeedometerUi(Clock *clock) : fxBlink() {
  }

  void tick(Clock *clock) {    
    PulseToSpeedStatus::Status status = pulseToSpeedStatus->getStatus();
    fxFade.tick( clock );
    fxBlink.tick( clock );
    
    if( status == PulseToSpeedStatus::AcceleratingOrConstant ) {
      updateAcceleratingOrConstant();
    } else if( status == PulseToSpeedStatus::Decelerating ) {
      updateDecelerating();
    } else if ( status == PulseToSpeedStatus::Stopped ) {
      updateStoped();
    }
    watchdog();
  }
  
private:

  void updateAcceleratingOrConstant() {
    fxFade.apply( acceleratingPin );
    deceleratingPin->set( false );
  }

  void updateDecelerating() {
    acceleratingPin->set( 0 );
    deceleratingPin->set( true );
  }

  void updateStoped() {
    acceleratingPin->set( 0 );
    fxBlink.apply( deceleratingPin );
  }

};

#endif

