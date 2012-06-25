
#ifndef __BikeLedSpeedometerUi_h__
#define __BikeLedSpeedometerUi_h__

#include "DigitalWritablePin.h"
#include "AnalogWritablePin.h"
#include "PulseToSpeedStatus.h"
#include "FxFade.h"

extern DigitalWritablePin *stoppedPin;
extern AnalogWritablePin *acceleratingPin, *deceleratingPin;
extern PulseToSpeedStatus *pulseToSpeedStatus;

class BikeLedSpeedometerUi {
  
  FxFade fxFade;
  PulseToSpeedStatus::Status oldStatus;
  
public:

  BikeLedSpeedometerUi(Clock *clock) {
    oldStatus = PulseToSpeedStatus::Stopped;
    fxFade.setDelay( 500, clock );
  }

  void tick(Clock *clock) {    
    PulseToSpeedStatus::Status status = pulseToSpeedStatus->getStatus();
    fxFade.tick( clock );
    
    if( status == PulseToSpeedStatus::AcceleratingOrConstant ) {
      updateAcceleratingOrConstant();
    } else if( status == PulseToSpeedStatus::Decelerating ) {
      updateDecelerating();
    } else if ( status == PulseToSpeedStatus::Stopped ) {
      updateStoped();
    }
    
    oldStatus = status;
  }
  
private:

  void updateAcceleratingOrConstant() {
    fxFade.apply( acceleratingPin );
    deceleratingPin->set( 0 );
  }

  void updateDecelerating() {
    acceleratingPin->set( 0 );
    deceleratingPin->set( 255 );
  }

  void updateStoped() {
    acceleratingPin->set( 0 );
    fxFade.apply( deceleratingPin );
  }

};

#endif

