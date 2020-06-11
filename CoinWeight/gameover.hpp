//
//  gameover.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameover_hpp
#define gameover_hpp

#include "gamescreen.hpp"

namespace CoinWeight {
  
  

class GameOver final : public GameScreenBase {
public:
    GameOver(const bool doesPlayerWin);
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(ViewX11 &view) const override;
    
private:
    bool playerWin;
};



};

#endif
