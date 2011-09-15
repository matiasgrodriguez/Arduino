
#ifndef __GameButtonGestures_h__
#define __GameButtonGestures_h__

#include "PushButton.h"

extern PushButton playerOneButton, playerTwoButton;

class GameButtonGestures {
  
public:

  void tick(Clock *clock) {
    playerOneButton.tick( clock );
    playerTwoButton.tick( clock );
  }
  
  bool wasButtonOnePressed() {
    return playerOneButton.wasPushed();
  }
  
  bool wasButtonTwoPressed() {
    return playerTwoButton.wasPushed();
  }
  
  bool wasButtonOneAndTwoPressed() {
    return false;
  }

};

#endif

