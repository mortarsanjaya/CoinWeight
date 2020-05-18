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
    
    void highlightUp(GameController &view) override;
    void highlightDown(GameController &view) override;
    void highlightLeft(GameController &view) override;
    void highlightRight(GameController &view) override;
    void onCharInput(GameController &view, const char inputChar) override;
    void onReturnButton(GameController &view) override;
    void triggerDisplay(GameController &view, GameUI &interface) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
};

#endif
