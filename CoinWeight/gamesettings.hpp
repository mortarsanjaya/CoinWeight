//
//  gamesettings.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesettings_hpp
#define gamesettings_hpp

#include "gamescreen.hpp"
#include "gamelevel.hpp"
#include "gamemode.hpp"
#include <utility>

namespace CoinWeight {



class GameSettings final : public GameScreenBase {
public:
    enum class Highlight {
        NumOfCoins,
        Level,
        Mode,
        StartGame,
        GoBack
    };
    
    GameSettings();
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(View &view) override;
    
private:
    Highlight highlight;

    static size_t nCoins;
    static GameLevel level;
    static GameMode mode;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
    static constexpr size_t numOfCoinsLowerBound = 3;
    static constexpr size_t numOfCoinsUpperBound = 200;
    static constexpr size_t defaultNumOfCoins = numOfCoinsLowerBound;
    static constexpr GameLevel defaultLevel = GameLevel::Easy;
    static constexpr GameMode defaultMode = GameMode::Standard;
    
    void increaseNumOfCoins();
    void decreaseNumOfCoins();
    void increaseLevel();
    void decreaseLevel();
    void nextMode();
    void prevMode();
};



};

#endif
