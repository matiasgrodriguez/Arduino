
#include "ArduinoClock.h"
#include "ArduinoDigitalPin.h"
#include "ArduinoAnalogWritablePin.h"
#include "PulseCounter.h"
#include "PulseToSpeedStatus.h"
#include "PinEffect.h"
#include "SoftPwmAnalogWritablePin.h"

//hardware
DigitalPin *pulsePin;
DigitalWritablePin /**acceleratingPin, */*deceleratingPin, *stoppedPin;
AnalogWritablePin *acceleratingPin;
Clock *clock;

//logic
PulseCounter *pulseCounter;
PulseToSpeedStatus *pulseToSpeedStatus;

SoftPwmAnalogWritablePin *softPwm;

void updatePins(bool,bool,bool);

void setup() {
  //Serial.begin(9600);
  
  clock = new ArduinoClock();
  pulsePin = new ArduinoDigitalPin( 6, INPUT );
  //acceleratingPin = new ArduinoDigitalPin( 5, OUTPUT );
  acceleratingPin = new ArduinoAnalogWritablePin( 3 );
  deceleratingPin = new ArduinoDigitalPin( 4, OUTPUT );
  stoppedPin = new ArduinoDigitalPin( 5, OUTPUT );
  
  pulseCounter = new PulseCounter( pulsePin );
  pulseToSpeedStatus = new PulseToSpeedStatus( pulseCounter );
  
  updatePins( false, false, false );
  
  uint8_t pwm = 255;
  softPwm = new SoftPwmAnalogWritablePin( stoppedPin, clock );
  softPwm->set( pwm );
  
  acceleratingPin->set( pwm );
}

void loop() {  
  //pulseCounter->tick( clock );
  //pulseToSpeedStatus->tick( clock );
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
  
  softPwm->tick( clock );
  //softPwm->apply( deceleratingPin );
}

void updatePins(bool acceleratingOrConstant, bool decelerating, bool stopped) {
  //acceleratingPin->set( acceleratingOrConstant );
  //deceleratingPin->set( decelerating );
  //stoppedPin->set( stopped );
}

