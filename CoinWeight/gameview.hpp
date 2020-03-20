//
//  gameview.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameview_hpp
#define gameview_hpp

#include <vector>
#include <utility>
#include "weighing.hpp"

class GameView {
public:
    GameView() = default;
    virtual void drawMainScreen(int screenHighlight) = 0;
    virtual void drawInstructionScreen() = 0;
    virtual void drawCreditScreen() = 0;
    virtual void drawGameOptionScreen(
        int screenHighlight, size_t numOfCoins,
        std::string gameLevel,
        bool isHuman) = 0;
    virtual void drawGamePlayScreen(
        std::vector<int> coinStates,
        int highlightedCoin,
        size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap,
        std::vector<std::pair<Weighing, int>> gameHistory) = 0;
    virtual void drawGameOverScreen(
        bool isWin,
        size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap,
        std::vector<size_t> finalGuess) = 0;
};

#endif
