
#ifndef __TimeControlUi_h__
#define __TimeControlUi_h__

#include <avr/pgmspace.h>
#include "TimeControl.h"

#define UI_BUFFER_SIZE 32

class TimeControlUi {

public:

  virtual const prog_char *getName() = 0;
  virtual int16_t getNumberOfOptions() = 0;
  virtual const prog_uint8_t *getOption(int16_t option) = 0;
  virtual TimeControl *create(int16_t option) = 0;
  
  virtual void render(Clock *clock, TimeControl *timeControl, uint8_t *buffer1, uint8_t *buffer2) = 0;
  
protected:
  
  void formatTime(int32_t time, uint8_t *buffer) {
    if( time <=0 ) {
      formatTimeNibble( 0, 0, buffer );
      return;
    }
    int32_t hours = time / ( 1000L * 60L * 60L );
    int32_t minutes = ( time % ( 1000L * 60L * 60L ) ) / ( 1000L * 60L );
    int32_t seconds = ( ( time % ( 1000L * 60L * 60L ) ) % ( 1000L * 60L ) ) / 1000L;
    //Serial.print( "Time: " );Serial.print( time );Serial.print( " hours: " );Serial.print( hours );Serial.print( " minutes: " );Serial.print( minutes );Serial.print( " seconds: " );Serial.println( seconds );
    if( hours > 0 ) {
      formatTimeNibble( hours, minutes, buffer );
    }else {
      formatTimeNibble( minutes, seconds, buffer );
    }
  }

private:

  void formatTimeNibble(int32_t left, int32_t right, uint8_t *buffer) {
    buffer[ 0 ] = ( uint8_t )( '0' + ( left / 10 ) );
    buffer[ 1 ] = ( uint8_t )( '0' + ( left % 10 ) );
    buffer[ 2 ] = ':';
    buffer[ 3 ] = ( uint8_t )( '0' + ( right / 10 ) );
    buffer[ 4 ] = ( uint8_t )( '0' + ( right % 10 ) );
  }

};

#endif

