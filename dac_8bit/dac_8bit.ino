
/**
How to build your own 8-bit DAC and play these tunes:
  http://matias.blog.br/2013/03/02/algorithmic-symphonies-from-one-line-of-code-meets-my-r-2r-diy-8bit-dac/

Result:
  http://www.youtube.com/watch?v=mPFx0IxGtb4

Have fun!
**/

#define DAC_PIN0 1
#define DAC_PIN1 2
#define DAC_PIN2 3
#define DAC_PIN3 4
#define DAC_PIN4 5
#define DAC_PIN5 6
#define DAC_PIN6 7
#define DAC_PIN7 8

#define BUTTON_NEXT_PIN 0

#define NUMBER_OF_TUNES 13

const int DELTA_IN_MICROS = 125; //8kHz: 1/8000 = 0.000125
int32_t t;
uint32_t nextSampleMicros;
int currentTune;

void sendToDac(byte sample) {  
  digitalWrite( DAC_PIN0, ( ( 1 << 0 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN1, ( ( 1 << 1 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN2, ( ( 1 << 2 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN3, ( ( 1 << 3 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN4, ( ( 1 << 4 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN5, ( ( 1 << 5 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN6, ( ( 1 << 6 ) & sample ) != 0 ? HIGH : LOW );
  digitalWrite( DAC_PIN7, ( ( 1 << 7 ) & sample ) != 0 ? HIGH : LOW );
}

uint8_t tune01() {
  return t*((t>>12|t>>8)&63&t>>4);
}
uint8_t tune02() {
  return (t*(t>>5|t>>8))>>(t>>16);
}
uint8_t tune03() {
  return t*((t>>9|t>>13)&25&t>>6);
}
uint8_t tune04() {
  return t*(t>>11&t>>8&123&t>>3);
}
uint8_t tune05() {
  return (t>>6|t|t>>(t>>16))*10+((t>>11)&7);
}
uint8_t tune06() {
  return (t|(t>>9|t>>7))*t&(t>>11|t>>9);
}
uint8_t tune07() {
  return t*5&(t>>7)|t*3&(t*4>>10);
}
uint8_t tune08() {
  return (t>>7|t|t>>6)*10+4*(t&t>>13|t>>6);
}
uint8_t tune09() {
  return ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6);
}
uint8_t tune10() {
  return t>>4|t&(t>>5)/(t>>7-(t>>15)&-t>>7-(t>>15));
}
uint8_t tune11() {
  return t*(t^t+(t>>15|1)^(t-1280^t)>>10);
}
uint8_t tune12() {
  return ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t));
}
uint8_t tune13() {
  return ((t*(t>>8|t>>9)&46&t>>14))^(9*t&t>>11|t>>6);
}

uint8_t (*tunes[ NUMBER_OF_TUNES ])() = { tune01, tune02, tune03, tune04, 
                                          tune05, tune06, tune07, tune08, 
                                          tune09, tune10, tune11, tune12,
                                          tune13 };

void playTuneNumber(int tune) {
  delay( 1000 );
  currentTune = tune;
  t = 0;
  nextSampleMicros = micros();
}

void checkButton() {
  static int buttonNextLastState = LOW;
  
  //suffers from bouncing, but it is Ok :)
  int buttonNext = digitalRead( BUTTON_NEXT_PIN );
  if( buttonNext == LOW && buttonNextLastState == HIGH  ) {
    playTuneNumber( currentTune == ( NUMBER_OF_TUNES - 1 ) ? 0 : currentTune + 1 );
  }
  buttonNextLastState = buttonNext;
}

void setup() {
  pinMode( DAC_PIN0, OUTPUT );
  pinMode( DAC_PIN1, OUTPUT );
  pinMode( DAC_PIN2, OUTPUT );
  pinMode( DAC_PIN3, OUTPUT );
  pinMode( DAC_PIN4, OUTPUT );
  pinMode( DAC_PIN5, OUTPUT );
  pinMode( DAC_PIN6, OUTPUT );
  pinMode( DAC_PIN7, OUTPUT );
  
  pinMode( BUTTON_NEXT_PIN, INPUT );
  
  playTuneNumber( 0 );
}

void loop() {
  checkButton();

  uint32_t timeMicros = micros();
  if( timeMicros < nextSampleMicros ) {
    return;
  }

  uint8_t sample = tunes[ currentTune ]();  
  sendToDac( sample );
  t++;
  
  nextSampleMicros = timeMicros + DELTA_IN_MICROS;
}

