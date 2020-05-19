//
//  gamesettings.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesettings_hpp
#define gamesettings_hpp

#include "modelstate.hpp"
#include "gamelevel.hpp"

class GameSettings final : public ModelState {
public:
    enum class Highlight {
        NumOfCoins,
        Level,
        Mode,
        StartGame,
        GoBack
    };
    
    GameSettings();
    
    const Highlight currHighlight() const;
    
    const size_t numOfCoins() const;
    const GameLevel gameLevel() const;
    const bool isHumanMode() const;
    
    void highlightUp() override;
    void highlightDown() override;
    void highlightLeft() override;
    void highlightRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(View &view) override;
    
private:
    Highlight highlight;

    static size_t nCoins;
    static GameLevel level;
    static bool isHuman;
    
    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
    static constexpr size_t numOfCoinsLowerBound = 3;
    static constexpr size_t numOfCoinsUpperBound = 200;
    static constexpr size_t defaultNumOfCoins = numOfCoinsLowerBound;
    static constexpr GameLevel defaultLevel = GameLevel::Easy;
    static constexpr bool defaultIsHuman = true;
    
    void increaseNumOfCoins();
    void decreaseNumOfCoins();
    void increaseLevel();
    void decreaseLevel();
    void switchMode();
};

#endif
