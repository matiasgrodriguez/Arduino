
#ifndef __TimeControlWithSound_h__
#define __TimeControlWithSound_h__

#include "TimeControl.h"
#include "Buzzer.h"

extern Buzzer buzzer;

class TimeControlWithSound : public TimeControl {
  
  TimeControl *delegate;

public:

  TimeControlWithSound() {
    delegate = NULL;
  }
  
  virtual ~TimeControlWithSound() {
  }
  
  void setDelegate(TimeControl *delegate) {
    this->delegate = delegate;
  }
  TimeControl *getDelegate() {
    return delegate;
  }
   
  virtual void setup(TimeTracker *playerOne, TimeTracker *playerTwo) {
    delegate->setup( playerOne, playerTwo );
  }

  virtual void onPlayerOneBeganToPlay() {
    buzzer.beepFor( 150 );
    delegate->onPlayerOneBeganToPlay();
  }
  
  virtual void onPlayerOnePlayed() {
    delegate->onPlayerOnePlayed();
  }
  
  virtual void onPlayerOneTimeExpired() {
    delegate->onPlayerOneTimeExpired();
  }

  virtual void onPlayerTwoBeganToPlay() {
    buzzer.beepFor( 150 );
    delegate->onPlayerTwoBeganToPlay();
  }
  
  virtual void onPlayerTwoPlayed() {
    delegate->onPlayerTwoPlayed();
  }
  
  virtual void onPlayerTwoTimeExpired() {
    delegate->onPlayerTwoTimeExpired();
  }
  
  virtual int32_t getPlayerOneTime(Clock *clock) {
    return delegate->getPlayerOneTime( clock );
  }
  
  virtual int32_t getPlayerTwoTime(Clock *clock) {
    return delegate->getPlayerTwoTime( clock );
  }
  
  virtual bool isOver()  {
    return delegate->isOver();
  }

};

#endif

