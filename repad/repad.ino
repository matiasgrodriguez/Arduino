
#include <Keypad.h>
#include <EEPROM.h>

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


#define LAYOUT_COMMANDS    9
#define LAYOUTS_COMMANDS   LAYOUT_COMMANDS*10

struct Layouts {
  int current;
  int index;
  byte indices[LAYOUTS_COMMANDS];
};

Layouts layouts;

void storeHardCodedValues() {
  const size_t MAX_SIZE = 256;
  byte commands[MAX_SIZE];
  memset(commands, 0, sizeof(commands));
  
  int i = 0;
  commands[i++] = BEGIN_BUFFER; //buffer start

  commands[i++] = BEGIN_KEY; //shortcut start: 0 eclipse previous
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = K_UP;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  commands[i++] = BEGIN_KEY; //shortcut start: 1 eclipse action
  commands[i++] = K_LCTRL;
  commands[i++] = '1';
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  commands[i++] = BEGIN_KEY; //shortcut start: 2 eclipse next
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = K_DOWN;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  commands[i++] = BEGIN_KEY; //shortcut start: 3 eclipse variable
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'l'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 
  
  commands[i++] = BEGIN_KEY; //shortcut start: 4 eclipse rename
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'r'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 
  
  commands[i++] = BEGIN_KEY; //shortcut start: 5 eclipse method
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'm'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 

  commands[i++] = BEGIN_KEY; //shortcut start: 6 eclipse ?
  
  commands[i++] = BEGIN_KEY; //shortcut start: 7 eclipse inline
  commands[i++] = K_LALT;
  commands[i++] = K_LSHIFT;
  commands[i++] = 'i'; 
  commands[i++] = WAIT; 
  commands[i++] = RELEASEALL; 
  
  commands[i++] = BEGIN_KEY; //shortcut start: 8 eclipse ?
  
  ////////////
  
  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper previous
  commands[i++] = K_LALT;
  commands[i++] = K_PAGEUP;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper action
  commands[i++] = K_LALT;
  commands[i++] = K_ENTER;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper next
  commands[i++] = K_LALT;
  commands[i++] = K_PAGEDOWN;
  commands[i++] = WAIT;
  commands[i++] = RELEASEALL;

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

  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper ?

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

  commands[i++] = BEGIN_KEY; //shortcut start: 0 resharper ?

  commands[i++] = END_BUFFER; 
  
  for(int i = 0; i < MAX_SIZE; ++i) {
    byte command = commands[ i ];
    EEPROM.write( i, command );
    if( command == END_BUFFER ) {
      break;
    }
  }
}

void setupCommands() {
  if( EEPROM.read( 0 ) != BEGIN_BUFFER ) {
    storeHardCodedValues();
  }
  
  memset(&layouts, 0, sizeof(layouts));
  for(int i = 0; i < 512; ++i) {
    byte command = EEPROM.read( i );
    if( command == BEGIN_KEY ) {
      layouts.indices[ layouts.index++ ] = i;
    } else if( command == END_BUFFER ) {
      break;
    }
  }
}

void execute(int button) {
  const size_t abortValue = 1000;
  //Serial.print( "execute: " );Serial.println( button );
  for(int i = layouts.indices[layouts.current + button] + 1; ; ++i) {
    byte command = EEPROM.read( i );
    //Serial.print( "i: " );Serial.print( i );Serial.print( " cmd: " );Serial.println( command );
    if( BEGIN_KEY == command || END_BUFFER == command || 0 == command ) { //peek
      break;
    }
    if( WAIT == command ) {
      //Serial.println( "wait" );
      wait();
    } else if( RELEASE == command ) {
      byte k = EEPROM.read( ++i );
      //Serial.print( "release " );Serial.println( k );
      releasekey( k );
    } else if( RELEASEALL == command ) {
      //Serial.println( "releaseall" );
      releaseall();
    } else {
      //Serial.println( "key" );
      k( command );
    }
    
    if( i >= abortValue ) {
      //Serial.println( "watchdog out" );
      break;
    }
  }
  //Serial.println( "execute end" );
}

///////////////////////////////////////////////////////////////////////////////////////////

void menu1() {
  layouts.current += LAYOUT_COMMANDS;
  if( layouts.current >= layouts.index ) {
    layouts.current = 0;
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



