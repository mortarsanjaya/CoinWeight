//
//  gameui.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameui_hpp
#define gameui_hpp

#include "gamelevel.hpp"
#include "weighresult.hpp"
#include "guessresult.hpp"
#include "coinselection.hpp"
#include "history.hpp"
#include "input.hpp"
#include "weighcounter.hpp"
#include "ScreenPages/allinclude.hpp"

class GameUI {
private:
//**** Virtual hook methods
    // General
    virtual void drawWeighResultText(const WeighResult weighResult) = 0;
    virtual void drawCoin(const CoinSelection::Group coinState, const size_t index) = 0;
    virtual void drawReturnButton() = 0;
    
    // Game Play screen
    virtual void drawGamePlayNumOfWeighs(const WeighCounter &counter) = 0;
    virtual void drawGamePlayHumanHighlight(const GamePlayHumanScreen &screen) = 0;
        
    // Game Over screen
    virtual void drawGameOverEndMessage(const GuessResult guessResult) = 0;
    virtual void drawGameOverNumOfWeighs(const WeighCounter &counter) = 0;
    
    /*
    // History screen
    virtual void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) = 0;
    virtual void drawEmptyHistoryScreen() = 0;
    */
    
    // Screen clearing
    virtual void clearScreen() = 0;
    
//**** Private non-virtual methods
    void drawCoins(const CoinSelection &coinStates);
    void drawRecord(const Record &record);
    void drawHistoryScreen(const Record &record, const size_t index, const size_t numOfWeighs);
    
public:
    GameUI() = default;
    virtual ~GameUI() = 0;
    
    // Drawing functions
    virtual void drawTitleScreen(const TitleScreen &screen) = 0;
    virtual void drawInstructionScreen(const InstructionScreen &screen) = 0;
    virtual void drawCreditScreen(const CreditScreen &screen) = 0;
    virtual void drawGameOptionScreen(const GameOptionScreen &screen) = 0;
        
    void drawGamePlayHumanScreen(const CoinSelection &coinStates, const GamePlayHumanScreen &screen,
        const WeighCounter &counter, const WeighResult lastWeighResult);
    void drawGamePlayComputerScreen(const CoinSelection &coinStates, const GamePlayComputerScreen &screen,
        const WeighCounter &counter, const WeighResult lastWeighResult);
    void drawGameOverScreen(const GuessResult guessResult, const WeighCounter &counter);
    
    // Input handling functions
    virtual void receiveInput() = 0;
    virtual const Input lastInput() = 0;
};

#endif
