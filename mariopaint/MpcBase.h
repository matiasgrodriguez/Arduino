
#ifndef __MpcBase_h__
#define __MpcBase_h__

#include "base.h"

struct MpcTone {
  uint8_t instrument;
  uint16_t note;
};

struct MpcBeat {
  //uint8_t volume;
  uint8_t numberOfTones;
  MpcTone *tones;
};

struct MpcMusic {
  uint16_t delay;
  uint8_t numberOfBeats;
  MpcBeat *beats;
};

#endif __MpcBase_h__

