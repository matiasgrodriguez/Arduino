
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ ROWS ][ COLS ] = {
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'},
};

byte rowPins[ ROWS ] = {10, 9, 8, 7};
byte colPins[ COLS ] = {6, 5, 4, 3};

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

void refactorRenameEclipse() {
    lalt();lshift();k( 'r' );wait();
    releaseall();
}

void refactorExtractLocalVariableEclipse() {
    lalt();lshift();k( 'l' );wait();
    releaseall();
}

void refactorExtractMethodEclipse() {
    lalt();lshift();k( 'm' );wait();
    releaseall();
}

void refactorInlineEclipse() {
    lalt();lshift();k( 'i' );wait();
    releaseall();
}

///////////////////////////////////////////////////////////////////////////////////////////

void refactorRenameResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'r' );wait();
    releaseall();
}

void refactorExtractLocalVariableResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'v' );wait();
    releaseall();
}

void refactorExtractMethodResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'm' );wait();
    releaseall();
}

void refactorInlineResharper() {
    lctrl();k( 'r' );wait();
    releasekey( 'r' );wait();
    k( 'i' );wait();
    releaseall();
}

///////////////////////////////////////////////////////////////////////////////////////////

void nop() {}

void (*refactorRename)() = refactorRenameEclipse;
void (*refactorExtractLocalVariable)() = refactorExtractLocalVariableEclipse;
void (*refactorExtractMethod)() = refactorExtractMethodEclipse;
void (*refactorInline)() = refactorInlineEclipse;

///////////////////////////////////////////////////////////////////////////////////////////

void switchMapping() {
  if( refactorRename == refactorRenameEclipse ) {
    refactorRename = refactorRenameResharper;
    refactorExtractLocalVariable = refactorExtractLocalVariableResharper;
    refactorExtractMethod = refactorExtractMethodResharper;
    refactorInline = refactorInlineResharper;
  } else {
    refactorRename = refactorRenameEclipse;
    refactorExtractLocalVariable = refactorExtractLocalVariableEclipse;
    refactorExtractMethod = refactorExtractMethodEclipse;
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
  
  if( key == '*' ) {
    switchMapping();
    return;
  }
  
  if( key == '1' ) {
    refactorRename();
  } else if( key == '2' ) {
    refactorExtractLocalVariable();
  } else if( key == '5' ) {
    refactorInline();
  } else if( key == '3' ) {
    refactorExtractMethod();
  }
  
}



