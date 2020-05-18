//
//  instructionscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef instructionscreen_hpp
#define instructionscreen_hpp

#include "gamescreen.hpp"

class InstructionScreen final : public GameScreen {
public:
    InstructionScreen();
    
    void highlightUp(GameController &view) override;
    void highlightDown(GameController &view) override;
    void highlightLeft(GameController &view) override;
    void highlightRight(GameController &view) override;
    void onCharInput(GameController &view, const char inputChar) override;
    void onReturnButton(GameController &view) override;
    void triggerDisplay(GameController &view, GameUI &interface) override;
};

#endif
