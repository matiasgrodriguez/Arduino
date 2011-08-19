

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
TimeControl *timeControl;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void format(int32_t left, int32_t right, uint8_t *buffer) {
  buffer[ 0 ] = ( uint8_t )( '0' + ( left / 10 ) );
  buffer[ 1 ] = ( uint8_t )( '0' + ( left % 10 ) );
  buffer[ 2 ] = ':';
  buffer[ 3 ] = ( uint8_t )( '0' + ( right / 10 ) );
  buffer[ 4 ] = ( uint8_t )( '0' + ( right % 10 ) );
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

//bool flag = true;
void printTime() {
  uint8_t buffer[ 16 ];
  for(int i = 0; i < 16; ++i) {
    buffer[ i ] = ' ';
  }
  //buffer[ 16 ]=0;
  
  format( timeControl->getPlayerOneTime( clock ), buffer );
  format( timeControl->getPlayerTwoTime( clock ), &buffer[11] );
  //lcd.clear();
  lcd.setCursor( 0, 0 );
  /*if( flag ) {
    Serial.print( ( char )buffer[ 0 ] );Serial.print( ( char )buffer[ 1 ] );Serial.print( ( char )buffer[ 2 ] );Serial.print( ( char )buffer[ 3 ] );
    Serial.print( ( char )buffer[ 4 ] );Serial.print( ( char )buffer[ 5 ] );Serial.print( ( char )buffer[ 6 ] );Serial.print( ( char )buffer[ 7 ] );
    Serial.print( ( char )buffer[ 8 ] );Serial.print( ( char )buffer[ 9 ] );Serial.print( ( char )buffer[ 10 ] );Serial.print( ( char )buffer[ 11 ] );
    Serial.print( ( char )buffer[ 12 ] );Serial.print( ( char )buffer[ 13 ] );Serial.print( ( char )buffer[ 14 ] );Serial.println( ( char )buffer[ 15 ] );
    //flag = false;
  }*/
  lcd.print( (const char*)buffer );
  lcd.setCursor( 0, 1 );
  lcd.print( "Byo Yomi" );
}

TimeControl *createByoYomiTimeControl() {
  ByoYomiSetup byoYomiSetup;
  byoYomiSetup.time = 30L * 1000L;
  byoYomiSetup.numberOfPeriods = 3;
  byoYomiSetup.periods[ 0 ].numberOfPlays = 3;
  byoYomiSetup.periods[ 0 ].time = 25L * 1000L;
  byoYomiSetup.periods[ 1 ].numberOfPlays = 2;
  byoYomiSetup.periods[ 1 ].time = 20L * 1000L;
  byoYomiSetup.periods[ 2 ].numberOfPlays = 1;
  byoYomiSetup.periods[ 2 ].time = 15L * 1000L;
  
  return new ByoYomiTimeControl( byoYomiSetup );
}

void setup() {
  Serial.begin(9600);
  Serial.println( "-= BEGIN =-" );
  Serial.println( sizeof(GameClock) );
  Serial.println( sizeof(ByoYomiTimeControl) );
  
  lcd.begin( 16, 2 );
  
  clock = new ArduinoClock();
  timeControl = createByoYomiTimeControl(); 
  gameClock.setup( clock, timeControl ); 
  gameClock.selectPlayerOne();
  
  pinMode( 8, INPUT );
  pinMode( 9, INPUT );
}

void loop() {
  gameClock.tick();
  printTime();
  delay( 50 );
  
  //*
  int status = digitalRead( 8 );
  //Serial.print( "Pin 8: " );Serial.println( status );
  if( status == HIGH  ) {
    gameClock.selectPlayerOne();
  }else {
    status = digitalRead( 9 );
   // Serial.print( "Pin 9: " );Serial.println( status );
    if( status == HIGH ) {
      gameClock.selectPlayerTwo();
    }
  }//*/
}

