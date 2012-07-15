
#ifndef __SoftPwmAnalogWritablePin_h__
#define __SoftPwmAnalogWritablePin_h__

#include "Clock.h"
#include "AnalogWritablePin.h"
#include "DigitalWritablePin.h"

class SoftPwmAnalogWritablePin : public AnalogWritablePin {
  
  Clock *clock;
  DigitalWritablePin *pin;
  
  uint32_t nextInvertionTime;
  uint8_t dutyCycle;
  bool isOn;
  
public: 

  SoftPwmAnalogWritablePin(DigitalWritablePin *pin, Clock *clock) {
    this->pin = pin;
    this->clock = clock;
    nextInvertionTime = 0;
  }
  
  virtual void set(uint8_t value) {
    //On 16 MHz Arduino boards, this function has a resolution of four microseconds. 
    //On 8 MHz Arduino boards this function has a resolution of eight microseconds.
    dutyCycle = value;
    isOn = value != 0 ? true : false;
    nextInvertionTime = clock->currentTimeInMicros() + dutyCycle;
    updatePin();
  }

  void tick(Clock *clock) {
    uint32_t currentTime = clock->currentTimeInMicros();
    if( currentTime < nextInvertionTime || dutyCycle == 0 ) {
      return;
    }

    if( isOn ) {
      nextInvertionTime = currentTime + ( 255 - dutyCycle );// + 5000;
    } else {
      nextInvertionTime = currentTime + dutyCycle;
    }
    isOn = !isOn;
    updatePin();
  }
  
private: 

  void updatePin() {
    pin->set( isOn );
  }
  
};

#endif

