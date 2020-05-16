//
//  gamesettingsscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesettingsscreen_hpp
#define gamesettingsscreen_hpp

#include "gamescreen.hpp"

class GameSettingsScreen final : public GameScreen {
public:
    enum class Highlight {
        NumOfCoins,
        Level,
        Mode,
        StartGame,
        GoBack
    };
    
    GameSettingsScreen();
    
    const Highlight currHighlight() const;
    
    void highlightUp(GameView &view) override;
    void highlightDown(GameView &view) override;
    void highlightLeft(GameView &view) override;
    void highlightRight(GameView &view) override;
    void onCharInput(GameView &view, const char inputChar) override;
    void onReturnButton(GameView &view) override;
    void triggerDisplay(GameUI &interface) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
};

#endif