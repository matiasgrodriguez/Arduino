
#ifndef __MpcBase_h__
#define __MpcBase_h__

#include "base.h"

#define MPC_BEAT_MAX_TONES            1
#define MPC_BEATCHUNK_MAX_BEATS      16

struct MpcTone {
  //uint8_t instrument;
  uint16_t note;
  
  MpcTone() {
    note = 0;
  }
};

struct MpcBeat {
  //uint8_t volume;
  uint8_t numberOfTones;
  MpcTone tones[ MPC_BEAT_MAX_TONES ];
  
  MpcBeat() {
    numberOfTones = 0;
  }
};

struct MpcBeatChunk {
  MpcBeat beats[ MPC_BEATCHUNK_MAX_BEATS ];
  MpcBeatChunk *next;
  
  MpcBeatChunk() {
    next = NULL;
  }
  
};

struct MpcMusic {
  uint16_t delay;
  uint8_t numberOfBeats; //fix this: uint16_t or remove (calculate instead)
  MpcBeatChunk beatChunk;
  
  MpcMusic() {
    delay = 0;
    numberOfBeats = 0;
  }
  
  MpcBeatChunk* getChunkAt(uint16_t index) {
    MpcBeatChunk *ret = &beatChunk;
    for(int16_t i = 0; i < index; ++i) {
      ret = ret->next;
    }
    return ret;
  }
  
  MpcBeat *getBeatAt(uint16_t index) {
    uint16_t chunk = index / MPC_BEATCHUNK_MAX_BEATS;
    uint16_t realIndex = index % MPC_BEATCHUNK_MAX_BEATS;
    return &( getChunkAt( chunk )->beats[ realIndex ] );
  }
  
};

#endif __MpcBase_h__

