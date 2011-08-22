
#include <avr/pgmspace.h>

#include <MemoryFree.h>

const prog_uint8_t option1[] PROGMEM = "KGS MEDIUM           25m +5(30s)";
const prog_uint8_t option2[] PROGMEM = "KGS FAST             10m +5(20s)";

const prog_uint8_t *table[] PROGMEM = {
  option1,
  option2
};

const prog_uint8_t *getString(uint8_t option) {
  return table[ option ];
}

void printOption(const prog_uint8_t *option) {
  uint8_t buffer[32];
  memcpy_P( buffer, option, 32 );
  
  for(int i = 0; i < 16; ++i) {
    Serial.print( ( char )buffer[i] );
  }
  Serial.println();
  for(int i = 0; i < 16; ++i) {
    Serial.print( buffer[i+16] );
  }
  Serial.println();
}

void setup() {
  Serial.begin( 9600 );
  
  printOption( getString( 0 ) );
  printOption( getString( 1 ) );
  printOption( getString( 1 ) );
  printOption( getString( 0 ) );
  
  Serial.print("freeMemory=");
  Serial.println(freeMemory());
}


void loop() {
}

