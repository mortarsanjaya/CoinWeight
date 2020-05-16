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
    
    void highlightUp(GameView &view) override;
    void highlightDown(GameView &view) override;
    void highlightLeft(GameView &view) override;
    void highlightRight(GameView &view) override;
    void onCharInput(GameView &view, const char inputChar) override;
    void onReturnButton(GameView &view) override;
    void triggerDisplay(GameUI &interface) override;
};

#endif
