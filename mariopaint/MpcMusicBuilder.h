
#ifndef __MpcMusicBuilder_h__
#define __MpcMusicBuilder_h__

#include "MpcBase.h"

class MpcMusicBuilder {
  
  MpcMusic *music;
  uint16_t currentChunk;
  uint16_t currentBeat;
  
public:

  MpcMusicBuilder &newMusicWithDelay(uint16_t delay) {
    music = new MpcMusic();
    music->delay = delay;
    currentChunk = 0;
    currentBeat = 0;
    
    return *this;
  }
  
  MpcMusicBuilder *nextBeat(){
    if( currentBeat == MPC_BEATCHUNK_MAX_BEATS - 1 ) {
      music->getChunkAt( currentChunk )->next = new MpcBeatChunk();
      currentChunk ++;
      currentBeat = 0;
    } else {
      currentBeat++;
    }
    music->numberOfBeats++;
    return this;
  }
  
  MpcMusicBuilder *newTone(uint16_t frequency){
    MpcTone *tone = &music->getChunkAt( currentChunk )->beats[ currentBeat ].tones[ 0 ];
    if( tone->note == 0 ) {
      //MMM. Supporting only one tone per beat.
      tone->note = frequency;
    }
    return this;
  }
  
  MpcMusic *build() {
    MpcMusic * ret = music;
    music = NULL;
    return ret;
  }

};

#endif

