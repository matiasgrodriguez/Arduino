
#ifndef __MpcMusicParser_h__
#define __MpcMusicParser_h__

#include "MpcMusicBuilder.h"
#include "InputStream.h"

#define MPC_PARESER_ERROR_INVALIDTIMESIGNATURE  1
#define MPC_PARESER_ERROR_INVALIDASTERISK       2
#define MPC_PARESER_ERROR_EOFREADINGBEAT        3
#define MPC_PARESER_ERROR_INVALIDBEAT           4
#define MPC_PARESER_ERROR_EOFREADINGVOLUME      5

class MpcMusicParser {
  
  InputStream *stream;
  MpcMusicBuilder *builder;
  uint8_t error;
  
public:

  MpcMusicParser(MpcMusicBuilder *mpcMusicBuilder, InputStream *is) {
    builder = mpcMusicBuilder;
    stream = is;
    error = 0;
  }
  virtual ~MpcMusicParser() {
  }
  
  MpcMusic *parse() {
    dumpMusic( "1" );
    if( !parseTimeSignature() ) {
      return NULL;
    }
    dumpMusic( "2" );
    if( !parseAsterisk() ) {
      return NULL;
    }
    
    if( !parseBeats() ) {
      dumpMusic( "3" );
      return NULL;
    }
    
    dumpMusic( "4" );
    return builder->build();
  }
  
  uint8_t getError() {
    return error;
  }
  
private:

  bool parseTimeSignature() {
     uint8_t chunk[3];
     int16_t read = stream->read( (uint8_t*)&chunk, 0, 3 );
     if( read != 3 ) {
       error = MPC_PARESER_ERROR_INVALIDTIMESIGNATURE;
       return false;
     }
     //MMM: calculate delay given time. Ex: 4/4 = ?ms
     builder->newMusicWithDelay( 100 );
     return true;
  }
  
  bool parseAsterisk() {
     int16_t byte = stream->read();
     if( byte == -1 || ( uint8_t ) byte != '*' ) {
       error = MPC_PARESER_ERROR_INVALIDASTERISK;
       return false;
     }
     return true;
  }
  
  bool parseBeats() {
    while( true ) {
      int16_t probe = stream->read();
      uint8_t byteInProbe = ( uint8_t )probe;
      if( probe == -1 || byteInProbe == '\0' ) {
        return true;//end of srtream, OK.
      }
      if( !parseBeat( byteInProbe ) ) {
        return false;
      }
    }
  }
  
  bool parseBeat(uint8_t byteInProbe) {
    if( byteInProbe == ':' ) {
      //empty beat...
      Serial.println( "->New Empty Beat" );
      builder->nextBeat();
      return true;
    }
    Serial.println( "->New Beat" );
    int16_t probe;
    for(uint16_t i = 0; i < 6; ++i) {
      if( !parseTone( byteInProbe ) ) {
        return false;
      }
      if( i < 5 ) {
        probe = stream->read();
        if( probe == -1 ) {
          error = MPC_PARESER_ERROR_EOFREADINGBEAT;
          return false;
        }
        byteInProbe = ( uint8_t )probe;
      }
    }
    if( !parseVolume() ){
      return false;
    }
    builder->nextBeat();    
    return true;
  }

  bool parseTone(uint16_t byteInProbe) {
    if( byteInProbe == '+' ) {
      Serial.println( "tone: empty" );
      return true;
    }
    uint8_t chunk[ 3 ];
    int16_t read = stream->read( ( uint8_t* )&chunk, 0, 2 );
    if( read != 2 ) {
      error = MPC_PARESER_ERROR_EOFREADINGBEAT;
      return false;
    }
    if( chunk[ 1 ] != '+' ) {
      //a sharp/flat note (accidental note), read an extra character...
      read = stream->read( ( uint8_t* )&chunk, 2, 1 );
      if( read != 1 ) {
        error = MPC_PARESER_ERROR_EOFREADINGBEAT;
        return false;
      }
      if( chunk[ 2 ] != '+' ) {
        error = MPC_PARESER_ERROR_INVALIDBEAT;
        return false;
      }
      read = 3;
    }
    
    uint8_t instrument = byteInProbe;
    uint16_t note = convertMpcCharNoteToNoteFrequency( ( uint8_t *)chunk, read == 3 );
    Serial.print( "instrument: " );Serial.print( (char)instrument );Serial.print( " tone: " );Serial.print( ( char )chunk[ 0 ] );Serial.print( ( char )chunk[ 1 ] );Serial.print( " frequency: " );Serial.println( note );
    builder->newTone( instrument, note );
    return true;  
  }
  
  boolean parseVolume() {
    uint8_t chunk[ 2 ]; 
    int16_t read = stream->read( ( uint8_t* )chunk, 0, 2 );
    if( read != 2 ) {
      error = MPC_PARESER_ERROR_EOFREADINGVOLUME;
      return false;
    }
    Serial.print( "Volume: " );Serial.println( (char)chunk[ 0 ] );
    //volume: chunk[0], ignore rest.
    return true;
  }
  
  bool hasError() {
    return error != 0;
  }
  
  uint16_t convertMpcCharNoteToNoteFrequency(uint8_t *note, bool accidentalNote) {
    uint16_t index = lookUpIndexGivenNoteChar( note[0] );
    if( accidentalNote ) {
      index = note[ 1 ] == '#' ? 1 : -1;
    }
    return MpcNotesTable[ index ][ 0 ];
  }
  
  uint16_t lookUpIndexGivenNoteChar(uint8_t mpcNote) {
    for(int i = 0; i < 28; ++i) {
      if( MpcNotesTable[ i ][ 1 ] == mpcNote ) {
        return i;
      }
    }
    return 1;//ERROR
  }
  
  void dumpMusic(const char* str) {
    MpcMusic *music = builder->build();
    Serial.print( str );Serial.print( " Music delay: " );Serial.print( ( int )music->delay ); Serial.print( " beats: " );Serial.println( ( int )music->numberOfBeats );
  }

};

#endif

