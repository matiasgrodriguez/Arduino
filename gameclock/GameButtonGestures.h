
#ifndef __GameButtonGestures_h__
#define __GameButtonGestures_h__

#include "PushButton.h"

extern PushButton playerOneButton, playerTwoButton;

class GameButtonGestures {
  
  uint32_t playerOneButtonPushedTime;
  uint32_t playerTwoButtonPushedTime;
  uint32_t currentTime;
  bool playerOneButtonPushed;
  bool playerTwoButtonPushed;
  
public:

  void tick(Clock *clock) {
    currentTime = clock->currentTime();
    playerOneButton.tick( clock );
    playerTwoButton.tick( clock );
    
    playerOneButtonPushed = playerOneButton.wasPushed();
    if( playerOneButtonPushed ) {
      playerOneButtonPushedTime = currentTime;
    }

    playerTwoButtonPushed = playerTwoButton.wasPushed();
    if( playerTwoButtonPushed ) {
      playerTwoButtonPushedTime = currentTime;
    }
  }
  
  bool wasButtonOnePressed() {
    if( !wasButtonPressed( playerOneButtonPushed, playerOneButtonPushedTime ) ) {
      return false;
    }
    playerOneButtonPushed = false;
    return true;
  }
  
  bool wasButtonTwoPressed() {
    if( !wasButtonPressed( playerTwoButtonPushed, playerTwoButtonPushedTime ) ) {
      return false;
    }
    playerTwoButtonPushed = false;
    return true;
  }
  
  bool wasButtonOneAndTwoPressed() {
    return false;
  }

private:

  bool wasButtonPressed(bool playerButtonPushed, uint32_t playerButtonPushedTime) {
    if( !playerButtonPushed || ( currentTime - playerButtonPushedTime > 20 ) ) {
      return false;
    }
    return true;
  }

};

#endif

