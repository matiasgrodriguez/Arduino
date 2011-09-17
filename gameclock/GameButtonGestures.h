
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
    
    if( !playerOneButtonPushed ) {
      playerOneButtonPushed = playerOneButton.wasPushed();
      if( playerOneButtonPushed ) {
        playerOneButtonPushedTime = currentTime;
      }
    }

    playerTwoButtonPushed = playerTwoButton.wasPushed();
    if( playerTwoButtonPushed ) {
      playerTwoButtonPushedTime = currentTime;
    }
  }
  
  bool wasButtonOnePressed() {
    return wasButtonPressed( &playerOneButtonPushed, playerOneButtonPushedTime );
  }
  
  bool wasButtonTwoPressed() {
    return wasButtonPressed( &playerTwoButtonPushed, playerTwoButtonPushedTime );
  }
  
  bool wasButtonOneAndTwoPressed() {
    bool bothButtonsWherePressed = playerOneButtonPushed && playerTwoButtonPushed;
    if( bothButtonsWherePressed ) {
      playerOneButtonPushed = false;
      playerTwoButtonPushed = false;
    }
    return bothButtonsWherePressed;
  }

private:

  bool wasButtonPressed(bool *playerButtonPushed, uint32_t playerButtonPushedTime) {
    if( !wasButtonPressedConsideringTreshold( *playerButtonPushed, playerOneButtonPushedTime ) ) {
      return false;
    }
    *playerButtonPushed = false;
    return true;
  }

  bool wasButtonPressedConsideringTreshold(bool playerButtonPushed, uint32_t playerButtonPushedTime) {
    return playerButtonPushed && ( currentTime - playerButtonPushedTime > 10 );
  }

};

#endif

