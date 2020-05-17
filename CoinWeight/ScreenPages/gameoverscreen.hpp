//
//  gameoverscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameoverscreen_hpp
#define gameoverscreen_hpp

#include "gamescreen.hpp"

class GameOverScreen final : public GameScreen {
public:
    
    GameOverScreen(const bool doesPlayerWin);
    
    const bool doesPlayerWin() const;
    
    void highlightUp(GameView &view) override;
    void highlightDown(GameView &view) override;
    void highlightLeft(GameView &view) override;
    void highlightRight(GameView &view) override;
    void onCharInput(GameView &view, const char inputChar) override;
    void onReturnButton(GameView &view) override;
    void triggerDisplay(GameView &view, GameUI &interface) override;
    
private:
    bool playerWin;
};

#endif
