
#ifndef __PushButton_h__
#define __PushButton_h__

#include <WProgram.h>

#include "base.h"
#include "SignalFilter.h"

class PushButton {
  
  SignalFilter filter;
  uint8_t pin;
  bool wasDown;

public:

  PushButton(uint8_t pin) : filter( 3 ) {
    this->pin = pin;
    wasDown = false;
  }
  
  void init() {
    pinMode( pin, INPUT );
    digitalWrite( pin, HIGH ); // http://sheepdogguides.com/arduino/aht0bounce1.htm
  }
  
  void tick(Clock *clock) {
    filter.tick( clock, digitalRead( pin ) );
    if( wasDown && isUp() ) {
      wasDown = false;
    }
  }
  
  bool isUp() {
    return !isDown();
  }

  bool isDown() {
    return filter.isOn();
  }
  
  bool wasPushed() {
    if( !wasDown ) {
      if( isDown() ) {
        wasDown = true;
      }
      return wasDown;
    }
    return false;
  }

};

#endif

