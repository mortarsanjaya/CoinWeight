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
    
    void highlightUp(Controller &view) override;
    void highlightDown(Controller &view) override;
    void highlightLeft(Controller &view) override;
    void highlightRight(Controller &view) override;
    void onCharInput(Controller &view, const char inputChar) override;
    void onReturnButton(Controller &view) override;
    void triggerDisplay(Controller &view, View &interface) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
};

#endif
