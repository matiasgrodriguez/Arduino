
#include <Keypad.h>

const byte ROWS = 3; 
const byte COLS = 3; 
char keys[ ROWS ][ COLS ] = {
  {'0','1','2'},
  {'3','4','5'},
  {'6','7','8'},
};

byte rowPins[ ROWS ] = {10, 9, 8};
byte colPins[ COLS ] = {6, 5, 4};

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

void (*eclipse[9])() = {
  previousEclipse,actionEclipse,nextEclipse,
  refactorExtractLocalVariableEclipse,refactorRenameEclipse,refactorExtractMethodEclipse,
  nop,refactorInlineEclipse, menu1
};

void (*resharper[9])() = {
  previousResharper,actionResharper,nextResharper,
  refactorExtractLocalVariableResharper,refactorRenameResharper,refactorExtractMethodResharper,
  nop,refactorInlineResharper, menu1
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
  if( offset >= 0 && offset < 9 ) {
    lookup[offset]();
  }
}



