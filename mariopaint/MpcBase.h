
#ifndef __MpcBase_h__
#define __MpcBase_h__

#include "base.h"

#define MPC_BEAT_MAX_TONES            1
#define MPC_BEATCHUNK_MAX_BEATS      16

struct MpcTone {
  //uint8_t instrument;
  uint16_t note;
};

struct MpcBeat {
  //uint8_t volume;
  uint8_t numberOfTones;
  MpcTone tones[ MPC_BEAT_MAX_TONES ];
};

struct MpcBeatChunk {
  MpcBeat beats[ MPC_BEATCHUNK_MAX_BEATS ];
  MpcBeatChunk *next;
};

struct MpcMusic {
  uint16_t delay;
  uint8_t numberOfBeats;
  MpcBeatChunk beatChunk;
};

#endif __MpcBase_h__

