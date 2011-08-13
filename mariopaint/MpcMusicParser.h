
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
    if( !parseTimeSignature() ) {
      return NULL;
    }
    if( !parseAsterisk() ) {
      return NULL;
    }
    if( !parseBeat() ) {
      return NULL;
    }
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
     builder->newMusicWithDelay( 1200 );
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
  
  bool parseBeat() {
    int16_t probe = stream->read();
    if( probe == -1 ) {
      error = MPC_PARESER_ERROR_EOFREADINGBEAT;
      return false;
    }
    uint8_t byteInProbe = ( uint8_t )probe;
    if( byteInProbe == ';' ) {
      //empty beat...
      Serial.println( "-> Empty Beat" );
      builder->nextBeat();
      return true;
    }
    Serial.println( "-> New Beat" );
    for(uint16_t i = 0; i < 6; ++i) {
      if( !parseTone( ( uint8_t )probe ) ) {
        return false;
      }
      if( i < 5 ) {
        probe = stream->read();
        if( probe == -1 ) {
          error = MPC_PARESER_ERROR_EOFREADINGBEAT;
          return false;
        }
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
    
    //instrument: probe, note: chunk[0] or chunk[0-1] '+': last byte read
    uint16_t note = convertMpcCharNoteToNoteFrequency( ( uint8_t *)chunk, read == 3 );
    Serial.print( "tone: " );Serial.print( chunk[ 0 ] );Serial.print( chunk[ 1 ] );Serial.print( " frequency: " );Serial.println( note );
    builder->newTone( note );
    return true;  
  }
  
  boolean parseVolume() {
    uint8_t chunk[ 3 ]; 
    int16_t read = stream->read( ( uint8_t* )chunk, 0, 3 );
    if( read != 3 ) {
      error = MPC_PARESER_ERROR_EOFREADINGVOLUME;
      return false;
    }
    Serial.print( "Volume: " );Serial.println( (char)chunk[ 0 ] );
    //volume: chunk[0], ignore rest.
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

};

#endif

