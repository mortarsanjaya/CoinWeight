//
//  gameview.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameview_hpp
#define gameview_hpp

#include "coingroup.hpp"
#include "gamelevel.hpp"
#include "weighresult.hpp"
#include "guessresult.hpp"
#include "coinstates.hpp"
#include "history.hpp"
#include "input.hpp"
#include "ScreenPages/allinclude.hpp"

class GameView {
private:
//**** Virtual hook methods
    // General
    virtual void drawWeighResultText(const WeighResult weighResult) = 0;
    virtual void drawCoin(const CoinGroup coinState, const size_t index) = 0;
    virtual void drawReturnButton() = 0;
    
    // Game Play screen
    virtual void drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) = 0;
    virtual void drawGamePlayHumanHighlight(const GamePlayHumanScreen::ScreenHighlight screenHighlight,
        const size_t coinHighlight) = 0;
        
    // Game Over screen
    virtual void drawGameOverEndMessage(const GuessResult guessResult) = 0;
    virtual void drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) = 0;
    
    /*
    // History screen
    virtual void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) = 0;
    virtual void drawEmptyHistoryScreen() = 0;
    */
    
    // Screen clearing
    virtual void clearScreen() = 0;
    
//**** Private non-virtual methods
    void drawCoins(const CoinStates &coinStates);
    void drawRecord(const Record &record);
    void drawHistoryScreen(const Record &record, const size_t index, const size_t numOfWeighs);
    
public:
    GameView() = default;
    virtual ~GameView() = 0;
    
    // Drawing functions
    virtual void drawTitleScreen(const TitleScreen &screen) = 0;
    virtual void drawInstructionScreen(const InstructionScreen &screen) = 0;
    virtual void drawCreditScreen(const CreditScreen &screen) = 0;
    virtual void drawGameOptionScreen(const GameOptionScreen &screen) = 0;
        
    void drawGamePlayHumanScreen(const CoinStates &coinStates, const GamePlayHumanScreen::ScreenHighlight screenHighlight,
        const size_t coinHighlight, const size_t numOfWeighsLeft, const size_t numOfWeighsMax, const WeighResult lastWeighResult);
    void drawGamePlayComputerScreen(const CoinStates &coinStates, const size_t numOfWeighsLeft,
        const size_t numOfWeighsMax, const WeighResult lastWeighResult);
    void drawGameOverScreen(const GuessResult guessResult, const size_t numOfWeighsLeft, const size_t numOfWeighsMax);
    
    // Input handling functions
    virtual void receiveInput() = 0;
    virtual const Input lastInput() = 0;
};

#endif
