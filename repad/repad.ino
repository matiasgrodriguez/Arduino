
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ ROWS ][ COLS ] = {
  { '0',  '1',  '2'},
  { '3',  '4',  '5'},
  { '6',  '7',  '8'},
  { '9', '10', '11'},
};

byte rowPins[ ROWS ] = {7, 6, 5, 15};
byte colPins[ COLS ] = {14, 16, 8};

int delayMillis = 30;

Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

void lalt() {
  Keyboard.press( KEY_LEFT_ALT );
}

void lshift() {
  Keyboard.press( KEY_LEFT_SHIFT );
}

void lctrl() {
  Keyboard.press( KEY_LEFT_CTRL );
}

void pageup() {
  Keyboard.press( KEY_PAGE_UP );
}

void pagedown() {
  Keyboard.press( KEY_PAGE_DOWN );
}

void enter() {
  Keyboard.press( KEY_RETURN );
}

void k(const char key) {
  Keyboard.press( key );
}

void wait() {
  delay( delayMillis );
}

void releaseall() {
  Keyboard.releaseAll();
}

void releasekey(const char key) {
  Keyboard.release(key);
}

///////////////////////////////////////////////////////////////////////////////////////////

void previousEclipse() {
}

void actionEclipse() {
    lctrl();k( '1' );wait();
    releaseall();
}

void nextEclipse() {
}

void refactorExtractLocalVariableEclipse() {
    lalt();lshift();k( 'l' );wait();
    releaseall();
}

void refactorRenameEclipse() {
    lalt();lshift();k( 'r' );wait();
    releaseall();
}

void refactorExtractMethodEclipse() {
    lalt();lshift();k( 'm' );wait();
    releaseall();
}

//undef

void refactorInlineEclipse() {
    lalt();lshift();k( 'i' );wait();
    releaseall();
}

///////////////////////////////////////////////////////////////////////////////////////////

void previousResharper() {
  lalt();pageup();wait();
  releaseall();
}

void actionResharper() {
    lalt();enter();wait();
    releaseall();
}

void nextResharper() {
  lalt();pagedown();wait();
  releaseall();
}

void refactorExtractLocalVariableResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'v' );wait();
    releaseall();
}

void refactorRenameResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'r' );wait();
    releaseall();
}

void refactorExtractMethodResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'm' );wait();
    releaseall();
}

//undef

void refactorInlineResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'i' );wait();
    releaseall();
}

///////////////////////////////////////////////////////////////////////////////////////////

void nop() {}

void menu1();

const int SIZE=12;
void (*eclipse[SIZE])() = {
  previousEclipse, actionEclipse, nextEclipse,
  refactorExtractLocalVariableEclipse, refactorRenameEclipse, refactorExtractMethodEclipse,
  nop, refactorInlineEclipse, nop,
  menu1, nop, nop
};

void (*resharper[SIZE])() = {
  previousResharper, actionResharper, nextResharper,
  refactorExtractLocalVariableResharper, refactorRenameResharper, refactorExtractMethodResharper,
  nop, refactorInlineResharper, nop,
  menu1, nop, nop
};

void (**lookup)() = eclipse;

///////////////////////////////////////////////////////////////////////////////////////////

void menu1() {
  if( lookup == eclipse ) {
    lookup = resharper;
  } else {
    lookup = eclipse;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  //Serial.begin(9600);
  Keyboard.begin();
}

void loop(){
  char key = keypad.getKey();

  if( key == NO_KEY ){
    return;
  }
  
  int offset = (int)key - (int)'0';
  if( offset >= 0 && offset < SIZE ) {
    lookup[offset]();
  }
}



