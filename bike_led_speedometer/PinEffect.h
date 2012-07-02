
#ifndef __PinEffect_h__
#define __PinEffect_h__

#include "Clock.h"
#include "DigitalWritablePin.h"
#include "AnalogWritablePin.h"

#define BIT_SET( _one_, _number_, _bitToSet_ )     ( _number_ |= _one_ << _bitToSet_ )
#define BIT_CLEAR( _one_, _number_, _bitToSet_ )   ( ( _number_ ) &= ~( _one_ << ( _bitToSet_ ) ) )
#define BIT_TOGGLE( _one_, _number_, _bitToSet_ )  ( ( _number_ ) ^= _one_ << ( _bitToSet_ ) )
#define BIT_GET( _one_, _number_, _bitToGet_ )     ( (_number_) & ( _one_ << ( _bitToGet_ ) ) )

/*
http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c
Setting a bit
Use the bitwise OR operator (|) to set a bit.
 number |= 1 << x;
That will set bit x.

Clearing a bit
Use the bitwise AND operator (&) to clear a bit.
 number &= ~(1 << x);
That will clear bit x. You must invert the bit string with the bitwise NOT operator (~), then AND it.

Toggling a bit
The XOR operator (^) can be used to toggle a bit.
 number ^= 1 << x;
That will toggle bit x.

Checking a bit
You didn't ask for this but I might as well add it.
To check a bit, AND it with the bit you want to check:
 bit = number & (1 << x);
That will put the value of bit x into the variable bit.
*/

class PinEffect {
  
public:

  virtual void tick(Clock *clock) = 0;
  virtual void apply(DigitalWritablePin *pin) = 0;
  virtual void apply(AnalogWritablePin *pin) = 0;
  
};

#endif


