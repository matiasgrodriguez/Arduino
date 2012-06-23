
#include "ArduinoClock.h"
#include "ArduinoDigitalPin.h"
#include "ArduinoAnalogWritablePin.h"
#include "PulseCounter.h"
#include "PulseToSpeedStatus.h"
#include "PinEffect.h"
#include "BikeLedSpeedometerUi.h"

//hardware
DigitalPin *pulsePin;
DigitalWritablePin *deceleratingPin, *stoppedPin;
AnalogWritablePin *acceleratingPin;
Clock *clock;

//logic
PulseCounter *pulseCounter;
PulseToSpeedStatus *pulseToSpeedStatus;

BikeLedSpeedometerUi *bikeLedSpeedometerUi;

void setup() {
  //Serial.begin(9600);
  
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 6, INPUT );
  acceleratingPin = new ArduinoAnalogWritablePin( 3 );
  deceleratingPin = new ArduinoDigitalPin( 4, OUTPUT );
  stoppedPin = new ArduinoDigitalPin( 5, OUTPUT );
  
  pulseCounter = new PulseCounter( pulsePin );
  pulseToSpeedStatus = new PulseToSpeedStatus( pulseCounter );
  
  bikeLedSpeedometerUi = new BikeLedSpeedometerUi();
  
  //updatePins( false, false, false );
  //Serial.println( point1.part.integer );
}

void loop() {  
  pulseCounter->tick( clock );
  pulseToSpeedStatus->tick( clock );
  bikeLedSpeedometerUi->update();
}

