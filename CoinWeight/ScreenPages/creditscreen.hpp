//
//  creditscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef creditscreen_hpp
#define creditscreen_hpp

#include "gamescreen.hpp"

class CreditScreen final : public GameScreen {
public:
    CreditScreen();
    
    void highlightUp(GameView &view) override;
    void highlightDown(GameView &view) override;
    void highlightLeft(GameView &view) override;
    void highlightRight(GameView &view) override;
    void onCharInput(GameView &view, const char inputChar) override;
    void onReturnButton(GameView &view) override;
    void triggerDisplay(GameView &view, GameUI &interface) override;
};

#endif
