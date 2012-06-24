
#include "ArduinoClock.h"
#include "ArduinoDigitalPin.h"
#include "ArduinoAnalogWritablePin.h"
#include "PulseCounter.h"
#include "PulseToSpeedStatus.h"
#include "PinEffect.h"
#include "BikeLedSpeedometerUi.h"

//hardware
DigitalPin *pulsePin;
AnalogWritablePin *acceleratingPin, *deceleratingPin;
Clock *clock;

//logic
PulseCounter *pulseCounter;
PulseToSpeedStatus *pulseToSpeedStatus;

//ui
BikeLedSpeedometerUi *bikeLedSpeedometerUi;

void setup() {
  //Serial.begin(9600);
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 2, INPUT );
  acceleratingPin = new ArduinoAnalogWritablePin( 3 );
  deceleratingPin = new ArduinoAnalogWritablePin( 5 );
  
  pulseCounter = new PulseCounter( pulsePin );
  pulseToSpeedStatus = new PulseToSpeedStatus( pulseCounter );
  
  bikeLedSpeedometerUi = new BikeLedSpeedometerUi( clock );  
}

void loop() {  
  pulseCounter->tick( clock );
  pulseToSpeedStatus->tick( clock );
  bikeLedSpeedometerUi->tick( clock );
}

