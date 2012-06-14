
#include <arduino.h>

#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulseCounter.h"

DigitalPin *pulsePin;
Clock *clock;
PulseCounter *pulseCounter;

void setup() {
  Serial.begin(9600);
    
  pulsePin = new ArduinoDigitalPin( 5, INPUT );
  clock = new ArduinoClock();
  pulseCounter = new PulseCounter( pulsePin );  
}

void loop() {
  pulseCounter->tick( clock );
  Serial.print( "Time: " );Serial.println( pulseCounter->pulsesPerSecond() );
  
}


