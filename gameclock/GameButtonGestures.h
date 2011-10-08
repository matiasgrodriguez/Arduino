
#ifndef __GameButtonGestures_h__
#define __GameButtonGestures_h__

#include "PushButton.h"

extern PushButton playerOneButton, playerTwoButton, menuButton;

class GameButtonGestures {
  
public:

  void tick(Clock *clock) {
    playerOneButton.tick( clock );
    playerTwoButton.tick( clock );
    menuButton.tick( clock );
  }
  
  bool wasButtonOnePressed() {
    return playerOneButton.wasPushed();
  }
  
  bool wasButtonTwoPressed() {
    return playerTwoButton.wasPushed();
  }
  
  bool wasButtonThreePressed() {
    return menuButton.wasPushed();
  }

};

#endif

