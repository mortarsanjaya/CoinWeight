//
//  gamesettings.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesettings_hpp
#define gamesettings_hpp

#include "gamelevel.hpp"

class GameSettings {
    int numOfCoins;
    GameLevel level;
    bool isHuman;
    
    // Number of coins bound
    static const int numOfCoinsLowerBound;
    static const int numOfCoinsUpperBound;
    
public:
    GameSettings(int numOfCoins = 13, GameLevel level = GameLevel::Hard, bool isHuman = true);
    
    const int gameSize() const;
    const GameLevel gameLevel() const;
    const bool isHumanMode() const;
    
    void increaseGameSize();
    void decreaseGameSize();
    void increaseDifficulty();
    void decreaseDifficulty();
    void switchMode();
};

#endif
