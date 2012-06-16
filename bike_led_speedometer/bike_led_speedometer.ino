
#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulsesPerSecondCounter.h"
#include "Accelerometer.h"

DigitalPin *pulsePin;
Clock *clock;
PulsesPerSecondCounter *pulseCounter;
Accelerometer *accelerometer;

void setup() {
  Serial.begin(9600);
  
  pulsePin = new ArduinoDigitalPin( 5, INPUT );
  clock = new ArduinoClock();
  pulseCounter = new PulsesPerSecondCounter( pulsePin );
  accelerometer = new Accelerometer( pulseCounter );
}

void loop() {
  pulseCounter->tick( clock );
  accelerometer->tick( clock );

  Accelerometer::Status status = accelerometer->getStatus();

  Serial.print( "Status: " );
  if( status == Accelerometer::None ) {
      Serial.println( "None" );
  } else if( status == Accelerometer::Accelerating ) {
      Serial.println( "Accelerating" );
  } else if ( status == Accelerometer::Decelerating ) {
    Serial.println( "Decelerating" );
  }
  
}


