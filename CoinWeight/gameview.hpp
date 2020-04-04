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
#include "history.hpp"
#include "input.hpp"
#include "weighresult.hpp"

class GameView {
protected:
    enum class DrawingWindow { Main, History };

private:
    // Draw weigh result text
    virtual void drawWeighResultText(const DrawingWindow drawWindow,
        const WeighResult weighResult) = 0;
        
    // Draw coins
    virtual void drawCoin(const DrawingWindow drawWindow,
        const CoinStates::Value coinState, const size_t index) = 0;
    void drawCoins(const DrawingWindow drawWindow, const CoinStates &coinStates);
    
    // Draw history screen
    virtual void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) = 0;
    void drawRecord(const Record &record);
    virtual void drawEmptyHistoryScreen() = 0;
    void drawHistoryScreen(const Record &record, const size_t index,
        const size_t numOfWeighs);
    
public:
    GameView() = default;
    virtual ~GameView() = 0;
    
    // Drawing functions
    virtual void drawMainScreen(int screenHighlight) = 0;
    virtual void drawInstructionScreen() = 0;
    virtual void drawCreditScreen() = 0;
    virtual void drawGameOptionScreen(int screenHighlight, size_t numOfCoins,
        std::string gameLevel, bool isHuman) = 0;
    virtual void drawGamePlayHumanScreen(CoinStates coinStates, int screenHighlight,
        int highlightedCoin, size_t numOfWeighsLeft, size_t numOfWeighsCap) = 0;
    virtual void drawGamePlayComputerScreen(CoinStates coinStates,
        size_t numOfWeighsLeft, size_t numOfWeighsMax) = 0;
    virtual void drawGameOverScreen(bool isWin,
        size_t numOfWeighsLeft, size_t numOfWeighMax) = 0;
        
    void drawHistoryScreen(const History &history);
    
    // Input handling functions
    virtual void receiveInput() = 0;
    virtual const Input lastInput() = 0;
};

#endif
