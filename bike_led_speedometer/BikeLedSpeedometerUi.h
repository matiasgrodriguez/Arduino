
#ifndef __BikeLedSpeedometerUi_h__
#define __BikeLedSpeedometerUi_h__

#include "DigitalWritablePin.h"
#include "AnalogWritablePin.h"
#include "PulseToSpeedStatus.h"

extern DigitalWritablePin *deceleratingPin, *stoppedPin;
extern AnalogWritablePin *acceleratingPin;
extern PulseToSpeedStatus *pulseToSpeedStatus;

class BikeLedSpeedometerUi {
  
public:

  BikeLedSpeedometerUi() {
  }

  void update() {
    PulseToSpeedStatus::Status status = pulseToSpeedStatus->getStatus();
  
    if( status == PulseToSpeedStatus::AcceleratingOrConstant ) {
      updatePins( true, false, false );
    } else if ( status == PulseToSpeedStatus::Decelerating ) {
      updatePins( false, true, false );
    } else if ( status == PulseToSpeedStatus::Stopped ) {
      updatePins( false, false, true );
    } else {
      updatePins( true, true, true );
    }
  }
  
private:

  void updatePins(bool acceleratingOrConstant, bool decelerating, bool stopped) {
    acceleratingPin->set( acceleratingOrConstant ? 255 : 0g );
    deceleratingPin->set( decelerating );
    stoppedPin->set( stopped );
  }

};

#endif

