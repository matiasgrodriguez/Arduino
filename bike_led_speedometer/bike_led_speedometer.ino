
#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulseCounter.h"
#include "PulseToSpeedStatus.h"

DigitalPin *pulsePin;
DigitalWritablePin *acceleratingPin, *deceleratingPin, *stoppedPin;
Clock *clock;

PulseCounter *pulseCounter;
PulseToSpeedStatus *pulseToSpeedStatus;

void updatePins(bool,bool,bool);

void setup() {
  //Serial.begin(9600);
  
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 6, INPUT );
  acceleratingPin = new ArduinoDigitalPin( 5, OUTPUT );
  deceleratingPin = new ArduinoDigitalPin( 4, OUTPUT );
  stoppedPin = new ArduinoDigitalPin( 3, OUTPUT );
  
  pulseCounter = new PulseCounter( pulsePin );
  pulseToSpeedStatus = new PulseToSpeedStatus( pulseCounter );
  
  acceleratingPin->set( false );
  deceleratingPin->set( false );
  stoppedPin->set( false );
}

void loop() {  
  pulseCounter->tick( clock );
  pulseToSpeedStatus->tick( clock );
  PulseToSpeedStatus::Status status = pulseToSpeedStatus->getStatus();

  if( status == PulseToSpeedStatus::AcceleratingOrConstant ) {
//      Serial.println( "Accelerating" );
      updatePins( true, false, false );
  } else if ( status == PulseToSpeedStatus::Decelerating ) {
//    Serial.println( "Decelerating" );
    updatePins( false, true, false );
  } else if ( status == PulseToSpeedStatus::Stopped ) {
//    Serial.println( "Stopped" );
    updatePins( false, false, true );
  } else {
    updatePins( true, true, true );
  }
}

void updatePins(bool acceleratingOrConstant, bool decelerating, bool stopped) {
  acceleratingPin->set( acceleratingOrConstant );
  deceleratingPin->set( decelerating );
  stoppedPin->set( stopped );
}

