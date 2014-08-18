
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

//http://batchloaf.wordpress.com/2013/02/12/simple-trick-for-sending-characters-to-a-serial-port-in-windows/
//echo matiasserial >\\.\COM21

String last;

void serialLoop() {
  if( Serial.available() == 0 ){
    return;
  }
  
  Serial.print( "Last: " );Serial.println( last );
  String str = Serial.readStringUntil('\n');
  Serial.print( "Got: " );Serial.println( str );
  last = str;
}

///////////////////////////////////////////////////////////////////////////////////////////

#define K_LCTRL KEY_LEFT_CTRL
#define K_LALT KEY_LEFT_ALT
#define K_LSHIFT KEY_LEFT_SHIFT
#define K_PAGEUP KEY_PAGE_UP 
#define K_PAGEDOWN KEY_PAGE_DOWN
#define K_ENTER KEY_RETURN
#define K_UP KEY_UP_ARROW
#define K_DOWN KEY_DOWN_ARROW

#define BEGIN_BUFFER 1
#define BEGIN_KEY 2
#define END_BUFFER 4
#define WAIT 17
#define RELEASE 18
#define RELEASEALL 19

struct Layout {
  int *current;
  int eclipse[9];
  int resharper[9];
};

Layout layout;
byte commands[256];

void setupCommands() {
  memset(commands, 0, sizeof(commands));
  memset(&layout, 0, sizeof(layout));

  int i = 0;
  commands[i++] = 1; //buffer start

  layout.eclipse[0] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 eclipse previous
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = K_UP;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.eclipse[1] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 1 eclipse action
  commands[i++] = K_LCTRL;
  commands[i++] = '1';
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.eclipse[2] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 2 eclipse next
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = K_DOWN;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.eclipse[3] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 3 eclipse variable
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'l'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 
  
  layout.eclipse[4] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 4 eclipse rename
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'r'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 
  
  layout.eclipse[5] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 5 eclipse method
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'm'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 

  layout.eclipse[6] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 6 eclipse ?
  
  layout.eclipse[7] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 7 eclipse inline
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'i'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 
  
  layout.eclipse[8] = i;  
  commands[i++] = BEGIN_KEY; //shortcut start: 8 eclipse ?
  
  ////////////
  
  layout.resharper[0] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper previous
  commands[i++] = K_LALT;
  commands[i++] = K_PAGEUP;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[1] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper action
  commands[i++] = K_LALT;
  commands[i++] = K_ENTER;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[2] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper next
  commands[i++] = K_LALT;
  commands[i++] = K_PAGEDOWN;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[3] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper variable
  commands[i++] = K_LCTRL;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = RELEASE;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = 'v';
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[4] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper rename
  commands[i++] = K_LCTRL;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = RELEASE;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[5] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper method
  commands[i++] = K_LCTRL;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = RELEASE;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = 'm';
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[6] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper ?

  layout.resharper[7] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper inline
  commands[i++] = K_LCTRL;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = RELEASE;
  commands[i++] = 'r';
  commands[i++] = WAIT;
  commands[i++] = 'i';
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  layout.resharper[8] = i;
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper ?

  commands[i++] = END_BUFFER; //buffer end
  
  layout.current = layout.eclipse;
}

void execute(int button) {
  //Serial.print( "execute: " );Serial.println( button );
  for(int i = layout.current[button] + 1; ; ++i) {
    byte command = commands[ i ];
    //Serial.print( "i: " );Serial.print( i );Serial.print( " cmd: " );Serial.println( command );
    if( BEGIN_KEY == command || END_BUFFER == command ) { //peek
      break;
    }
    if( WAIT == command ) {
      //Serial.println( "wait" );
      wait();
    } else if( RELEASE == command ) {
      byte k = commands[ ++i ];
      //Serial.print( "release " );Serial.println( k );
      releasekey( k );
    } else if( RELEASEALL == command ) {
      //Serial.println( "releaseall" );
      releaseall();
    } else {
      //Serial.println( "key" );
      k( command );
    }
    
    if( i > 255 ) {
      //Serial.println( "watchdog out" );
      break;
    }
  }
  //Serial.println( "execute end" );
}

///////////////////////////////////////////////////////////////////////////////////////////

void menu1() {
  if( layout.current == layout.eclipse ) {
    layout.current = layout.resharper;
  } else {
    layout.current = layout.eclipse;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);
  Keyboard.begin();
  
  setupCommands();
}

void loop(){
  char key = keypad.getKey();
  
  serialLoop();

  if( key == NO_KEY ){
    return;
  }
  
  if( key == '9' ){
    menu1();
    return;
  }
  
  const int SIZE=9;
  int offset = (int)key - (int)'0';
  if( offset >= 0 && offset < SIZE ) {
    execute( offset );
  }
}



