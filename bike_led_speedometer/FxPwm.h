
#ifndef __FxPwm_h__
#define __FxPwm_h__

#include "PinEffect.h"

class FxPwm : public PinEffect {
  
  uint32_t timeOn;
  uint32_t timeOff;
  uint32_t nextInvertionTime;
  bool isOn;
  
  
public: 

  virtual void tick(Clock *clock) {
    uint32_t currentTime = micros();//FIX THIS
    if( currentTime < nextInvertionTime  ) {
      return;
    }
    
    if( isOn ) {
      nextInvertionTime = currentTime + timeOff;
    } else {
      nextInvertionTime = currentTime + timeOn;
    }
    
    isOn = !isOn;
  }
  
  virtual void apply(DigitalWritablePin *pin) {
    pin->set( isOn );
  }
  
  void setDutyCycle(uint8_t dutyCycle, Clock *clock) {
    timeOn = dutyCycle * 4; //On 16 MHz Arduino boards, this function has a resolution of four microseconds. On 8 MHz Arduino boards this function has a resolution of eight microseconds
    timeOff = ( 255 - dutyCycle ) * 4;
    
    isOn = true;
    nextInvertionTime = micros() + timeOn; //FIX THIS;
  }
  
};

#endif
