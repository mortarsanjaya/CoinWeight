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
#include <utility>

class GameSettings {
    size_t gameSize;
    GameLevel level;
    bool isHuman;
    
    // Number of coins bound
    static constexpr size_t numOfCoinsLowerBound = 3;
    static constexpr size_t numOfCoinsUpperBound = 200;
    
    static constexpr size_t defaultNumOfCoins = numOfCoinsLowerBound;
    static constexpr GameLevel defaultLevel = GameLevel::Easy;
    static constexpr bool defaultIsHuman = true;
    
public:
    GameSettings();
    
    const size_t numOfCoins() const;
    const GameLevel gameLevel() const;
    const bool isHumanMode() const;
    
    void increaseNumOfCoins();
    void decreaseNumOfCoins();
    void increaseLevel();
    void decreaseLevel();
    void switchMode();
};

#endif
