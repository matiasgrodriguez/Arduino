
#include "ArduinoDigitalPin.h"
#include "ArduinoClock.h"
#include "PulseCounter.h"

DigitalPin *pulsePin;
Clock *clock;
PulseCounter *pulseCounter;

void setup() {
  pulsePin = new ArduinoDigitalPin( 5, INPUT );
  clock = new ArduinoClock();
  pulseCounter = new PulseCounter( pulsePin );
}

void loop() {
  pulseCounter->tick( clock );
}


