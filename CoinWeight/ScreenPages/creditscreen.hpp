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
    
    void highlightUp(GameController &view) override;
    void highlightDown(GameController &view) override;
    void highlightLeft(GameController &view) override;
    void highlightRight(GameController &view) override;
    void onCharInput(GameController &view, const char inputChar) override;
    void onReturnButton(GameController &view) override;
    void triggerDisplay(GameController &view, GameUI &interface) override;
};

#endif
