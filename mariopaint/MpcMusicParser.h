
#ifndef __MpcMusicParser_h__
#define __MpcMusicParser_h__

#include "InputStream.h"

#define MPC_PARESER_ERROR_INVALIDTIMESIGNATURE  1
#define MPC_PARESER_ERROR_INVALIDASTERISK       2
#define MPC_PARESER_ERROR_EOFREDINGBEAT         3
#define MPC_PARESER_ERROR_INVALIDBEAT           4

class MpcMusicParser {
  
  InputStream *stream;
  uint8_t error;
  
public:

  MpcMusicParser(InputStream *is) {
    stream = is;
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
      error = MPC_PARESER_ERROR_EOFREDINGBEAT;
      return false;
    }
    uint8_t byteInProbe = ( uint8_t )probe;
    if( byteInProbe = ';' ) {
      //MMM. Create EMPTY BEAT.
      return true;
    }
    uint8_t chunk[2];
    int16_t read = stream->read( ( uint8_t* )&chunk, 0, 2 );
    if( read != 2 ) {
      error = MPC_PARESER_ERROR_EOFREDINGBEAT;
      return false;
    }
    if( chunk[1] != '+' ) {
      error = MPC_PARESER_ERROR_INVALIDBEAT;
      return false;
    }
    //byteInProbe == note
    //chunk[0] == instrument
    //chunk[1] == '+'
    
    
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

};

#endif

