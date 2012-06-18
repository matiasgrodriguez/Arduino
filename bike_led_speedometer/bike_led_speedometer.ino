
#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulseCounter.h"
#include "Accelerometer2.h"

DigitalPin *pulsePin;
DigitalWritablePin *acceleratingPin, *deceleratingPin, *nonePin, *stoppedPin;
Clock *clock;

PulseCounter *pulseCounter;
Accelerometer2 *accelerometer2;

void updatePins(bool,bool,bool,bool);

void setup() {
  Serial.begin(9600);
  
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 6, INPUT );
  acceleratingPin = new ArduinoDigitalPin( 5, OUTPUT );
  deceleratingPin = new ArduinoDigitalPin( 4, OUTPUT );
  nonePin = new ArduinoDigitalPin( 3, OUTPUT );
  stoppedPin = new ArduinoDigitalPin( 2, OUTPUT );
  
  pulseCounter = new PulseCounter( pulsePin );
  accelerometer2 = new Accelerometer2( pulseCounter );
  
  acceleratingPin->set( false );
  deceleratingPin->set( false );
  nonePin->set( false );
  stoppedPin->set( false );
}

void loop() {  
  pulseCounter->tick( clock );
  accelerometer2->tick( clock );
  Accelerometer2::Status status2 = accelerometer2->getStatus();

  if( status2 == Accelerometer2::None ) {
      Serial.println( "None" );
      updatePins( true, false, false, false );
  } else if( status2 == Accelerometer2::Accelerating ) {
      Serial.println( "Accelerating" );
      updatePins( false, true, false, false );
  } else if ( status2 == Accelerometer2::Decelerating ) {
    Serial.println( "Decelerating" );
    updatePins( false, false, true, false );
  } else if ( status2 == Accelerometer2::Stopped ) {
    Serial.println( "Stopped" );
    updatePins( false, false, false, true );
  }
}

void updatePins(bool none, bool accelerating, bool decelerating, bool stopped) {
  nonePin->set( none );
  acceleratingPin->set( accelerating );
  deceleratingPin->set( decelerating );
  stoppedPin->set( stopped );
}


