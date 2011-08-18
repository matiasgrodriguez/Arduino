

#include <LiquidCrystal.h>

#include "base.h"
#include "ManualClock.h"
#include "ArduinoClock.h"
#include "GameClock.h"
#include "TimeControlTest.h"
#include "SuddenDeathTimeControl.h"
#include "HourGlassTimeControl.h"
#include "FischerDelayTimeControl.h"
#include "ByoYomiTimeControl.h"

GameClock gameClock;
Clock *clock;
TimeControlTest timeControl( 20, 30 );
SuddenDeathTimeControl suddenDeathTc( 20L * 1000L );
HourGlassTimeControl hourGalssTc( 100 );
FischerDelayTimeControl fischerDelayTc( 100, 10 );
ByoYomiTimeControl byoYomiTc();

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void format(int32_t left, int32_t right, uint8_t *buffer) {
  //Serial.print( "left: " );Serial.print( left );Serial.print( " right: " );Serial.println( right );
  buffer[ 0 ] = ( uint8_t )( '0' + ( left / 10 ) );
  buffer[ 1 ] = ( uint8_t )( '0' + ( left % 10 ) );
  buffer[ 2 ] = ':';
  buffer[ 3 ] = ( uint8_t )( '0' + ( right / 10 ) );
  buffer[ 4 ] = ( uint8_t )( '0' + ( right % 10 ) );
  //str[ 5 ] = '\0';
}

void format(int32_t time, uint8_t *buffer) {
  if( time <=0 ) {
    format( 0, 0, buffer );
    return;
  }
  int32_t hours = time / ( 1000L * 60L * 60L );
  int32_t minutes = ( time % ( 1000L * 60L * 60L ) ) / ( 1000L * 60L );
  int32_t seconds = ( ( time % ( 1000L * 60L * 60L ) ) % ( 1000L * 60L ) ) / 1000L;
  //Serial.print( "Time: " );Serial.print( time );Serial.print( " hours: " );Serial.print( hours );Serial.print( " minutes: " );Serial.print( minutes );Serial.print( " seconds: " );Serial.println( seconds );
  if( hours > 0 ) {
    format( hours, minutes, buffer );
  }else {
    format( minutes, seconds, buffer );
  }
}

void printTime() {
  uint8_t buffer[ 16 ];
  buffer[ 15 ] = '\0';
  for(int i = 0; i < 16; ++i) {
    buffer[ i ] = ' ';
  }
  
  format( suddenDeathTc.getPlayerOneTime( clock ), buffer );
  format( suddenDeathTc.getPlayerTwoTime( clock ), &buffer[11] );
  //lcd.clear();
  lcd.setCursor( 0, 0 );
  lcd.print( (const char*)buffer );
  lcd.setCursor( 0, 1 );
  lcd.print( "BYO YOMI" );
}

void setup() {
  Serial.begin(9600);
  
  /*
  Serial.println( 23000L/(1000*60*60) );
  Serial.println( sizeof(int) );
  Serial.println( sizeof(long) );

  uint8_t buffer[6];
  format( 100L, buffer );
  Serial.println( ( char* )buffer );
  
  format( 1000L, buffer );
  Serial.println( ( char* )buffer );
  
  format( 23 * 1000L, buffer );
  Serial.println( ( char* )buffer );

  format( 60 * 1000L, buffer );
  Serial.println( ( char* )buffer );

  int32_t horas, minutos, segundos;
  
  horas = 7;
  minutos = 47;
  segundos = 38;
  format( horas * 60L * 60L * 1000L  + minutos * 60L * 1000L + segundos * 1000L, buffer );
  Serial.println( ( char* )buffer );
  */

  /*

  //clock = new ArduinoClock();  
  clock = new ManualClock();
  gameClock.setup( clock, &hourGalssTc );

  gameClock.tick();  
  clock->setCurrentTime( 1 );
  gameClock.tick();
  gameClock.selectPlayerOne();
  gameClock.tick();
  clock->setCurrentTime( 5 );
  gameClock.tick();
  gameClock.selectPlayerTwo();
  gameClock.tick();
  clock->setCurrentTime( 10 );
  gameClock.tick();
  gameClock.selectPlayerOne();
  clock->setCurrentTime( 20 );
  gameClock.tick();
  gameClock.selectPlayerTwo();
  gameClock.tick();
  clock->setCurrentTime( 25 );
  gameClock.selectPlayerOne();
  gameClock.tick();
  clock->setCurrentTime( 30 );
  gameClock.tick();
  clock->setCurrentTime( 31 );
  gameClock.tick();
  clock->setCurrentTime( 32 );
  gameClock.tick();
  clock->setCurrentTime( 33 );
  gameClock.tick();
  gameClock.selectPlayerTwo();
  clock->setCurrentTime( 53 );
  gameClock.tick();
  gameClock.selectPlayerOne();
  clock->setCurrentTime( 54 );
  gameClock.tick();
  */
  
  lcd.begin( 16, 2 );
  
  clock = new ArduinoClock();  
  gameClock.setup( clock, &suddenDeathTc ); 
  gameClock.selectPlayerOne();
  
  pinMode( 8, INPUT );
  pinMode( 7, OUTPUT );
  digitalWrite( 7, HIGH );
  digitalWrite( 8, LOW );
}


void loop() {
  gameClock.tick();
  printTime();
  delay( 50 );
  
  int status = digitalRead( 8 );
  if( status == HIGH  ) {
    gameClock.selectPlayerTwo();
  }
  
  //Serial.println( clock->currentTime() );
  //uint32_t currentTime = clock->currentTime();
  //Serial.println( currentTime );
  //manualClock.setCurrentTime( currentTime + 1 );
}

