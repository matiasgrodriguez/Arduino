
#ifndef __MpcBase_h__
#define __MpcBase_h__

#include "base.h"
#include "notes.h"

#define MPC_BEAT_MAX_TONES            1
#define MPC_BEATCHUNK_MAX_BEATS      16

uint16_t MpcNotesTable[][2] = {
  { NOTE_AS3, 0 },  // 0
  { NOTE_B3, 'p' }, // 1   p
  { NOTE_C4, 'o' }, // 2   o
  { NOTE_CS4, 0 },  // 3   
  { NOTE_D4, 'n' }, // 4   n
  { NOTE_DS4, 0 },  // 5   
  { NOTE_E4, 'm' }, // 6   m
  { NOTE_F4, 'l' }, // 7   l
  { NOTE_FS4, 0 },  // 8   
  { NOTE_G4, 'k' }, // 9   k
  { NOTE_GS4, 0 },  //10   
  { NOTE_A4, 'j' }, //11   j
  { NOTE_AS4, 0 },  //12   
  { NOTE_B4, 'i' }, //13   i
  { NOTE_C5, 'h' }, //14   h
  { NOTE_CS5, 0 },  //15   
  { NOTE_D5, 'g' }, //16   g
  { NOTE_DS5, 0 },  //17
  { NOTE_E5, 'f' }, //18   f
  { NOTE_F5, 'e' }, //19   e
  { NOTE_FS5, 0 },  //20   
  { NOTE_G5, 'd' }, //21   d
  { NOTE_GS5, 0 },  //22   
  { NOTE_A5, 'c' }, //23   c
  { NOTE_AS5, 0 },  //24   
  { NOTE_B5, 'b' }, //25   b
  { NOTE_C6, 'a' }, //26   a
  { NOTE_CS6, 0 },  //27   
};

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

