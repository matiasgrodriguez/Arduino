
#ifndef __FixedPoint_h__
#define __FixedPoint_h__

#include "base.h"

//#define FIXEDX_YCONST(A,B) (FULL-SIZEINT)((A<<Y) + ((B + 1/(2^(Y+1)))*2^Y))

//http://www.eetimes.com/discussion/other/4024639/Fixed-point-math-in-C
template <class FULL_SIZE_INT, int X, int Y> union FixedPoint {

public:

  FULL_SIZE_INT full;
  struct {
    FULL_SIZE_INT integer:X;
    FULL_SIZE_INT fraction:sizeof(FULL_SIZE_INT)-X;
  }part;

  FixedPoint() {
    full = 0;
  }

  FixedPoint(int integer, int fraction) {
    full = ( integer << Y ) + ( ( fraction + 1/( 2^( fraction+1 ) ) ) * 2^Y );
  }

  FixedPoint operator*(const FixedPoint &other) {
    return FixedPoint();
  }
  
};

#endif 
