
#ifndef __MpcMusicParser_h__
#define __MpcMusicParser_h__

#include "MpcMusicBuilder.h"
#include "InputStream.h"

#define MPC_PARESER_ERROR_INVALIDTIMESIGNATURE  1
#define MPC_PARESER_ERROR_INVALIDASTERISK       2
#define MPC_PARESER_ERROR_EOFREADINGBEAT        3
#define MPC_PARESER_ERROR_INVALIDBEAT           4

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
    //Serial.println( "1" );
    int16_t probe = stream->read();
    //Serial.println( probe );
    if( probe == -1 ) {
      error = MPC_PARESER_ERROR_EOFREADINGBEAT;
      return false;
    }
    //Serial.println( "2" );
    uint8_t byteInProbe = ( uint8_t )probe;
    if( byteInProbe == ';' ) {
      //empty beat...
      builder->nextBeat();
      return true;
    }
    //Serial.println( "3" );
    //parse tones...
    //Parse lj+ (intrument,note,'+')

    uint8_t chunk[ 3 ];
    int16_t read = stream->read( ( uint8_t* )&chunk, 0, 2 );
    //Serial.println( "4" );
    if( read != 2 ) {
      error = MPC_PARESER_ERROR_EOFREADINGBEAT;
      return false;
    }
    if( chunk[ 1 ] != '+' ) {
      //a sharp/flat note (accidental note)...
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
    //Serial.println( "5" );
    uint16_t note = convertMpcCharNoteToNoteFrequency( ( uint8_t *)chunk, read == 3 );
    Serial.print( "NOTE: " );Serial.println( note );
    builder->newTone( note );
    builder->nextBeat();    
    Serial.println( "6" );
    return true;
    /*
  void parseBeat() {
    //debug( "Begin beat Position", pos );
    debug( "Begin beat ", currentBeat );
    if( musicData->charAt( pos ) != ':' ) {
      currentTone = 0;
      for(int i = 0; i < 6; ++i) {
        parseTone();
        currentTone++;
      }
      parseVolume();
    }else {
      debug( "Empty Beat..." );
      pos++;
    }
    debug( "End beat Position", pos );
    currentBeat++;
    mpcMusic->totalBeats++;
  }
  */
  
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

