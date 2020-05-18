//
//  gamesettingsscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesettingsscreen_hpp
#define gamesettingsscreen_hpp

#include "modelstate.hpp"
#include "gamesettings.hpp"

class GameSettingsScreen final : public ModelState {
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
    
    void highlightUp(Controller &controller) override;
    void highlightDown(Controller &controller) override;
    void highlightLeft(Controller &controller) override;
    void highlightRight(Controller &controller) override;
    void onCharInput(Controller &controller, const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(Controller &controller, View &interface) override;
    
private:
    Highlight highlight;

    static GameSettings settings;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
};

#endif
