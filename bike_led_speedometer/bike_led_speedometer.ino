
#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulsesPerSecondCounter.h"
#include "Accelerometer.h"

DigitalPin *pulsePin;
DigitalWritablePin *acceleratingPin, *deceleratingPin, *nonePin;
Clock *clock;
PulsesPerSecondCounter *pulseCounter;
Accelerometer *accelerometer;

void updatePins(bool,bool,bool);

void setup() {
  Serial.begin(9600);
  
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 5, INPUT );
  acceleratingPin = new ArduinoDigitalPin( 4, OUTPUT );
  deceleratingPin = new ArduinoDigitalPin( 3, OUTPUT );
  nonePin = new ArduinoDigitalPin( 2, OUTPUT );
  
  pulseCounter = new PulsesPerSecondCounter( pulsePin );
  accelerometer = new Accelerometer( pulseCounter );
  
  acceleratingPin->set( false );
  deceleratingPin->set( false );
  nonePin->set( false );
}

void loop() {
  pulseCounter->tick( clock );
  accelerometer->tick( clock );

  Accelerometer::Status status = accelerometer->getStatus();

  Serial.print( "Status: " );
  if( status == Accelerometer::None ) {
      Serial.println( "None" );
      updatePins( true, false, false );
  } else if( status == Accelerometer::Accelerating ) {
      Serial.println( "Accelerating" );
      updatePins( false, true, false );
  } else if ( status == Accelerometer::Decelerating ) {
    Serial.println( "Decelerating" );
    updatePins( false, false, true );
  }
  
}

void updatePins(bool none, bool accelerating, bool decelerating) {
  nonePin->set( none );
  acceleratingPin->set( accelerating );
  deceleratingPin->set( decelerating );
}


