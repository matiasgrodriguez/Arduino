
#ifndef __ArduinoDigitalPin_h__
#define __ArduinoDigitalPin_h__

#include <Arduino.h>

#include "DigitalWritablePin.h"

class ArduinoDigitalPin : public DigitalWritablePin {
  
  uint8_t pin;
  
public:

  ArduinoDigitalPin(uint8_t pin, uint8_t mode) {
    this->pin = pin;
    pinMode( pin, mode );
  }

  virtual bool isSet() {
    return digitalRead( pin );
  }
  
  virtual void set(bool val) {
    digitalWrite( pin, val );
  }
  
  virtual void toggle() {
    set( !isSet() );
  }
  
};

#endif

