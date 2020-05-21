//
//  gameover.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameover_hpp
#define gameover_hpp

#include "modelstate.hpp"

namespace CoinWeight {
  
  

class GameOver final : public ModelState {
public:
    
    GameOver(const bool doesPlayerWin);
    
    void highlightUp() override;
    void highlightDown() override;
    void highlightLeft() override;
    void highlightRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(View &view) override;
    
private:
    bool playerWin;
};



};

#endif
