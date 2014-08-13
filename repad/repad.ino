
#include <Keypad.h>

const byte ROWS = 3; 
const byte COLS = 3; 
char keys[ ROWS ][ COLS ] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
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

void (*previous)() = previousEclipse;
void (*action)() = actionEclipse;
void (*next)() = nextEclipse;
void (*refactorExtractLocalVariable)() = refactorExtractLocalVariableEclipse;
void (*refactorRename)() = refactorRenameEclipse;
void (*refactorExtractMethod)() = refactorExtractMethodEclipse;
void (*undef)() = nop;
void (*refactorInline)() = refactorInlineEclipse;

///////////////////////////////////////////////////////////////////////////////////////////

void menu1() {
  if( refactorRename == refactorRenameEclipse ) {
    previous = previousResharper;
    action = actionResharper;
    next = nextResharper;
    refactorExtractLocalVariable = refactorExtractLocalVariableResharper;
    refactorRename = refactorRenameResharper;
    refactorExtractMethod = refactorExtractMethodResharper;
    undef = nop;
    refactorInline = refactorInlineResharper;
  } else {
    previous = previousEclipse;
    action = actionEclipse;
    next = nextEclipse;
    refactorExtractLocalVariable = refactorExtractLocalVariableEclipse;
    refactorRename = refactorRenameEclipse;
    refactorExtractMethod = refactorExtractMethodEclipse;
    undef = nop;
    refactorInline = refactorInlineEclipse;
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
  
  if( key == '1' ) {
    previous();
  } else if( key == '2' ) {
    action();
  } else if( key == '3' ) {
    next();
  } else if( key == '4' ) {
    refactorExtractLocalVariable();
  } else if( key == '5' ) {
    refactorRename();
  } else if( key == '6' ) {
    refactorExtractMethod();
  } else if( key == '7' ) {
    undef();
  } else if( key == '8' ) {
    refactorInline();
  } else if( key == '9' ) {
    menu1();
  }
  
}



