//
//  gameoptionscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameoptionscreen_hpp
#define gameoptionscreen_hpp

#include "gamesettings.hpp"

class GameOptionScreen {
public:
    enum class Highlight {
        NumOfCoins,
        Level,
        Mode
    };
    
    GameOptionScreen();
    
    const Highlight currHighlight() const;
    const GameSettings &currSettings() const;
    
    // Manual highlight switch
    void highlightSwitch(const Highlight highlight);
    
    // Reset highlight
    void resetHighlight();
    
    // Arrow button highlight switch
    void highlightUp();
    void highlightDown();
    void highlightLeft();
    void highlightRight();
    
private:
    Highlight highlight;
    static GameSettings settings;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
};

#endif
