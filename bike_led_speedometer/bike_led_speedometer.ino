
#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulseCounter.h"
#include "PulseToSpeedStatus.h"

DigitalPin *pulsePin;
DigitalWritablePin *acceleratingPin, *deceleratingPin, *nonePin, *stoppedPin;
Clock *clock;

PulseCounter *pulseCounter;
PulseToSpeedStatus *pulseToSpeedStatus;

void updatePins(bool,bool,bool,bool);

void setup() {
  //Serial.begin(9600);
  
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 6, INPUT );
  acceleratingPin = new ArduinoDigitalPin( 5, OUTPUT );
  deceleratingPin = new ArduinoDigitalPin( 4, OUTPUT );
  nonePin = new ArduinoDigitalPin( 3, OUTPUT );
  stoppedPin = new ArduinoDigitalPin( 2, OUTPUT );
  
  pulseCounter = new PulseCounter( pulsePin );
  pulseToSpeedStatus = new PulseToSpeedStatus( pulseCounter );
  
  acceleratingPin->set( false );
  deceleratingPin->set( false );
  nonePin->set( false );
  stoppedPin->set( false );
}

void loop() {  
  pulseCounter->tick( clock );
  pulseToSpeedStatus->tick( clock );
  PulseToSpeedStatus::Status status = pulseToSpeedStatus->getStatus();

  if( status == PulseToSpeedStatus::None ) {
//      Serial.println( "None" );
      updatePins( true, false, false, false );
  } else if( status == PulseToSpeedStatus::Accelerating ) {
//      Serial.println( "Accelerating" );
      updatePins( false, true, false, false );
  } else if ( status == PulseToSpeedStatus::Decelerating ) {
//    Serial.println( "Decelerating" );
    updatePins( false, false, true, false );
  } else if ( status == PulseToSpeedStatus::Stopped ) {
//    Serial.println( "Stopped" );
    updatePins( false, false, false, true );
  } else {
    updatePins( true, true, true, true );
  }
}

void updatePins(bool none, bool accelerating, bool decelerating, bool stopped) {
  nonePin->set( none );
  acceleratingPin->set( accelerating );
  deceleratingPin->set( decelerating );
  stoppedPin->set( stopped );
}


