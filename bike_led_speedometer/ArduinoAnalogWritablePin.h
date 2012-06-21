
#ifndef __ArduinoAnalogWritablePin_h__
#define __ArduinoAnalogWritablePin_h__

#include <Arduino.h>

#include "AnalogWritablePin.h"

class ArduinoAnalogWritablePin : public AnalogWritablePin {
  
  uint8_t pin;
  
public:

  ArduinoAnalogWritablePin(uint8_t pin) {
    this->pin = pin;
  }

  virtual void set(uint8_t value) {
    analogWrite( pin, value );
  }
  
};

#endif

