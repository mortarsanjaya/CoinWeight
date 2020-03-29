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
#include "coinstates.hpp"
#include "record.hpp"
#include "input.hpp"
#include "weighresult.hpp"

class GameView {
public:
    GameView() = default;
    
    // Drawing functions
    virtual void drawMainScreen(int screenHighlight) = 0;
    virtual void drawInstructionScreen() = 0;
    virtual void drawCreditScreen() = 0;
    virtual void drawGameOptionScreen(
        int screenHighlight,
        size_t numOfCoins,
        std::string gameLevel,
        bool isHuman) = 0;
    virtual void drawGamePlayScreen(
        CoinStates coinStates,
        int highlightedCoin,
        size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap,
        WeighResult lastWeighResult) = 0;
    virtual void drawGameOverScreen(
        bool isWin,
        size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap) = 0;
    virtual void drawGameHistoryScreen(
        std::vector<Record> gameHistory,
        size_t historyIndex) = 0;
        
    // Input handling functions
    virtual void receiveInput() = 0;
    virtual const Input lastInput() const = 0;
};

#endif
