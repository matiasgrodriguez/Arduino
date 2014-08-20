
#include <Keypad.h>
#include <EEPROM.h>

///////////////////////////////////////////////////////////////////////////////////////////

#define KEYPAD_ROWS                           4
#define KEYPAD_COLS                           3
#define KEYPAD_USER_KEYS                      9

char keys[ KEYPAD_ROWS ][ KEYPAD_COLS ] = {
  { '0',  '1',  '2'},
  { '3',  '4',  '5'},
  { '6',  '7',  '8'},
  { '9', '10', '11'},
};

byte rowPins[ KEYPAD_ROWS ] = {7, 6, 5, 15};
byte colPins[ KEYPAD_COLS ] = {14, 16, 8};

Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS );

///////////////////////////////////////////////////////////////////////////////////////////

#define EEPROM_SIZE                        1000

#define BUFFER_START                          1
#define KEY_START                             2
#define BUFFER_END                            4
#define WAIT                                 17
#define RELEASE                              18
#define RELEASEALL                           19

#define LAYOUT_COMMANDS                       9
#define LAYOUTS_COMMANDS   LAYOUT_COMMANDS * 10

struct Layouts {
  int keyOffset;
  unsigned int keyCount;
  byte indices[ LAYOUTS_COMMANDS ];
};

Layouts layouts;

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
  delay( 25 );
}

void releaseall() {
  Keyboard.releaseAll();
}

void releasekey(const char key) {
  Keyboard.release(key);
}

///////////////////////////////////////////////////////////////////////////////////////////

struct SerialUploadState {
  boolean allow;
  unsigned int address;
};

SerialUploadState serialUploadState;

void eeprom_write(int address, byte value) {
  if( EEPROM.read( address ) != value ) {
    EEPROM.write( address, value );
  }
}

void serialUploadIfAvailable() {
  if( Serial.available() == 0 ){
    return;
  }
  
  String line = Serial.readStringUntil( '\n' );

  if( line.length() == 0 ) {
    return;
  }  

  if( line.startsWith( "dump" ) ) {
    Serial.print( "Layouts> keyOffset: " );Serial.print( layouts.keyOffset );Serial.print( " keyCount " );Serial.println( layouts.keyCount );
    for(int i=0; i < layouts.keyCount; ++i) {
      Serial.print( i ); Serial.print( "> " ); Serial.println( layouts.indices[ i ] );
    }
    Serial.println( "EEPROM> content: " );
    for(int i=0; i < EEPROM_SIZE/2; ++i) {
      Serial.print( i ); Serial.print( "> " ); Serial.println( EEPROM.read(i) );
    }
    return;
  }
  
  if( line.startsWith( "bs" ) ) {
    serialUploadState.allow = true;
  }
  
  if( !serialUploadState.allow ) {
    return;
  }
  
  boolean needsToUpdateLayout = false;
  byte command = 0;
  
  if( line.startsWith( "bs" ) ) {
    serialUploadState.address = 0;
    command = BUFFER_START;
  } else if( line.startsWith( "ks" ) ) {
    command = KEY_START;
  } else if( line.startsWith( "wa" ) ) {
    command = WAIT;
  } else if( line.startsWith( "rk" ) ) {
    command = RELEASE;
  } else if( line.startsWith( "ralt" ) ) {
    command = KEY_RIGHT_ALT;
  } else if( line.startsWith( "ra" ) ) {
    command = RELEASEALL;
  } else if( line.startsWith( "be" ) ) {
    command = BUFFER_END; 
    needsToUpdateLayout = true;
    serialUploadState.allow = false;
  } else if( line.startsWith( "lctrl" ) ) {
    command = KEY_LEFT_CTRL;
  } else if( line.startsWith( "lshift" ) ) {
    command = KEY_LEFT_SHIFT;
  } else if( line.startsWith( "lalt" ) ) {
    command = KEY_LEFT_ALT;
  } else if( line.startsWith( "lgui" ) ) {
    command = KEY_LEFT_GUI;
  } else if( line.startsWith( "rctrl" ) ) {
    command = KEY_RIGHT_CTRL;
  } else if( line.startsWith( "rshift" ) ) {
    command = KEY_RIGHT_SHIFT;
  } else if( line.startsWith( "rgui" ) ) {
    command = KEY_RIGHT_GUI;
  } else if( line.startsWith( "up" ) ) {
    command = KEY_UP_ARROW;
  } else if( line.startsWith( "down" ) ) {
    command = KEY_DOWN_ARROW;
  } else if( line.startsWith( "left" ) ) {
    command = KEY_LEFT_ARROW;
  } else if( line.startsWith( "right" ) ) {
    command = KEY_RIGHT_ARROW;
  } else if( line.startsWith( "backspace" ) ) {
    command = KEY_BACKSPACE;
  } else if( line.startsWith( "tab" ) ) {
    command = KEY_TAB;
  } else if( line.startsWith( "enter" ) ) {
    command = KEY_RETURN;
  } else if( line.startsWith( "esc" ) ) {
    command = KEY_ESC;
  } else if( line.startsWith( "ins" ) ) {
    command = KEY_INSERT;
  } else if( line.startsWith( "del" ) ) {
    command = KEY_DELETE;
  } else if( line.startsWith( "pup" ) ) {
    command = KEY_PAGE_UP;
  } else if( line.startsWith( "pdown" ) ) {
    command = KEY_PAGE_DOWN;
  } else if( line.startsWith( "home" ) ) {
    command = KEY_HOME;
  } else if( line.startsWith( "end" ) ) {
    command = KEY_END;
  } else if( line.startsWith( "capsl" ) ) {
    command = KEY_CAPS_LOCK;
  } else if( line.startsWith( "f10" ) ) {
    command = KEY_F10;
  } else if( line.startsWith( "f11" ) ) {
    command = KEY_F11;
  } else if( line.startsWith( "f12" ) ) {
    command = KEY_F12;
  } else if( line.startsWith( "f1" ) ) {
    command = KEY_F1;
  } else if( line.startsWith( "f2" ) ) {
    command = KEY_F2;
  } else if( line.startsWith( "f3" ) ) {
    command = KEY_F3;
  } else if( line.startsWith( "f4" ) ) {
    command = KEY_F4;
  } else if( line.startsWith( "f5" ) ) {
    command = KEY_F5;
  } else if( line.startsWith( "f6" ) ) {
    command = KEY_F6;
  } else if( line.startsWith( "f7" ) ) {
    command = KEY_F7;
  } else if( line.startsWith( "f8" ) ) {
    command = KEY_F8;
  } else if( line.startsWith( "f9" ) ) {
    command = KEY_F9;
  } else {
    command = line.charAt(0);
  }

  eeprom_write( serialUploadState.address++, command );
  
  if( needsToUpdateLayout ) {
    setupLayouts();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////

void storeHardCodedValues() {
  byte commands[] = { BUFFER_START, KEY_START, KEY_START, KEY_START, KEY_START, KEY_START, KEY_START, KEY_START, KEY_START, KEY_START, BUFFER_END };
 
  for(int i = 0; ; ++i) {
    byte command = commands[ i ];
    eeprom_write( i, command );
    if( command == BUFFER_END ) {
      break;
    }
  }
}

void setupLayouts() {
  if( EEPROM.read( 0 ) != BUFFER_START ) {
    storeHardCodedValues();
  }
  
  memset(&layouts, 0, sizeof(layouts));
  for(int i = 0; i < EEPROM_SIZE; ++i) {
    byte command = EEPROM.read( i );
    if( command == KEY_START ) {
      layouts.indices[ layouts.keyCount++ ] = i;
    } else if( command == BUFFER_END ) {
      break;
    }
  }
}

void execute(int button) {
  Serial.print( "execute: " );Serial.println( button );
  for(int i = layouts.indices[layouts.keyOffset + button] + 1; ; ++i) {
    byte command = EEPROM.read( i );
    Serial.print( "i: " );Serial.print( i );Serial.print( " cmd: " );Serial.println( command );
    if( KEY_START == command || BUFFER_END == command || 0 == command ) {
      break;
    }
    if( WAIT == command ) {
      Serial.println( "wait" );
      wait();
    } else if( RELEASE == command ) {
      byte k = EEPROM.read( ++i );
      Serial.print( "release " );Serial.println( k );
      releasekey( k );
    } else if( RELEASEALL == command ) {
      Serial.println( "releaseall" );
      releaseall();
    } else {
      Serial.print( "key: " );Serial.println( command );
      k( command );
    }
    
    if( i >= EEPROM_SIZE ) {
      break;
    }
  }
  Serial.println( " " );
}

///////////////////////////////////////////////////////////////////////////////////////////

void menu1() {
  layouts.keyOffset += LAYOUT_COMMANDS;
  if( layouts.keyOffset >= layouts.keyCount ) {
    layouts.keyOffset = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  memset(&serialUploadState, 0, sizeof(serialUploadState));
  
  Serial.begin(9600);
  Keyboard.begin();
  
  setupLayouts();
}

void loop(){
  char key = keypad.getKey();
  
  serialUploadIfAvailable();

  if( key == NO_KEY ){
    return;
  }
  
  if( key == '9' ){
    menu1();
    return;
  }
  
  int offset = key - '0';
  if( offset >= 0 && offset < KEYPAD_USER_KEYS ) {
    execute( offset );
  }
}

