
#ifndef __GameClockLcd_h__
#define __GameClockLcd_h__

#include <avr/pgmspace.h>
#include <LiquidCrystal.h>

#define GAME_CLOCK_LCD_BUFFER_SIZE 17

class GameClockLcd {
  
  enum Alignment { Left, Center, Right };
  
  LiquidCrystal lcd;
  char buffer1[ GAME_CLOCK_LCD_BUFFER_SIZE ];
  char buffer2[ GAME_CLOCK_LCD_BUFFER_SIZE ];
  
public:

  GameClockLcd(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : lcd( rs, enable, d0, d1, d2, d3 ) {
  }
  
  void beginRender() {
    clearBuffer( buffer1 );
    clearBuffer( buffer2 );
  }
  
  //void printTimeAtLeft(int32_t time) {
  //}
  
  void printTopLeft(const prog_char *str) {
    printAligned( str, buffer1, Left );
  }

  void printTopCenter(const prog_char *str) {
    printAligned( str, buffer1, Center );
  }

  void printTopRight(const prog_char *str) {
    printAligned( str, buffer1, Right );
  }

  void printBottomLeft(const prog_char *str) {
    printAligned( str, buffer2, Left );
  }

  void printBottomCenter(const prog_char *str) {
    printAligned( str, buffer2, Center );
  }

  void printBottomRight(const prog_char *str) {
    printAligned( str, buffer2, Right );
  }
  
  void printWholeScreen(const prog_char *str) {
    memcpy_P( buffer1, str, GAME_CLOCK_LCD_BUFFER_SIZE - 1 );
    memcpy_P( buffer2, &str[ GAME_CLOCK_LCD_BUFFER_SIZE - 1 ], GAME_CLOCK_LCD_BUFFER_SIZE - 1 );
  }
  
  void printTopLeftTime(int32_t time) {
    formatTime( time, buffer1 );
  }
  
  void printTopRightTime(int32_t time) {
    formatTime( time, &buffer1[ 11 ] );
  }
  
  void sPrintBottomLeft(const prog_char *format, ...) {
    va_list body;
    va_start( body, format );
    sPrint( buffer2, Left, format, body );
    va_end(body);
  }

  void sPrintBottomCenter(const prog_char *format, ...) {
    va_list body;
    va_start( body, format );
    sPrint( buffer2, Center, format, body );
    va_end(body);
  }

  void sPrintBottomRight(const prog_char *format, ...) {
    va_list body;
    va_start( body, format );
    sPrint( buffer2, Right, format, body );
    va_end( body );
  }

  void endRender() {
    lcd.setCursor( 0, 0 );
    lcd.print( buffer1 );
    lcd.setCursor( 0, 1 );
    lcd.print( buffer2 );
  }
  
private:

  void clearBuffer(char *buffer) {
    int16_t lastPosition = GAME_CLOCK_LCD_BUFFER_SIZE - 1; 
    memset( buffer, ' ', lastPosition );
    buffer[ lastPosition ] = '\0';
  }
  
  void printAligned(const prog_char *str, char *screenBuffer, Alignment aligment) {
    char buffer[ GAME_CLOCK_LCD_BUFFER_SIZE ];
    strcpy_P( buffer, str );
    printAlignedUsingLocalBuffer( buffer, screenBuffer, aligment );
  }

  void printAlignedUsingLocalBuffer(const char *buffer, char *screenBuffer, Alignment aligment) {
    int16_t length = strlen( buffer );
    int16_t index = 0;
    if( aligment == Center ) {
      index = ( GAME_CLOCK_LCD_BUFFER_SIZE - length ) / 2;
    } else if( aligment == Right ) {
      index = GAME_CLOCK_LCD_BUFFER_SIZE - 1 - length;
    }
    memcpy( &screenBuffer[ index ], buffer, length );
  }

  void formatTime(int32_t time, char *buffer) {
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
  
  void formatTimeNibble(int32_t left, int32_t right, char *buffer) {
    buffer[ 0 ] = ( char )( '0' + ( left / 10 ) );
    buffer[ 1 ] = ( char )( '0' + ( left % 10 ) );
    buffer[ 2 ] = ':';
    buffer[ 3 ] = ( char )( '0' + ( right / 10 ) );
    buffer[ 4 ] = ( char )( '0' + ( right % 10 ) );
  }
  
  void sPrint(char *screenBuffer, Alignment aligment, const prog_char *format, va_list body) {
    char buffer[ GAME_CLOCK_LCD_BUFFER_SIZE ];
    vsprintf_P(buffer, format, body);
    printAlignedUsingLocalBuffer( buffer, screenBuffer, aligment );
  }

  
};

#endif
