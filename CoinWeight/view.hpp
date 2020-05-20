//
//  view.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef view_hpp
#define view_hpp

#include "title.hpp"
#include "instruction.hpp"
#include "credit.hpp"
#include "gamesettings.hpp"
#include "gameplayhuman.hpp"
#include "gameplaycomputer.hpp"
#include "gameover.hpp"

#include "coinselection.hpp"
#include "weighresult.hpp"
#include "weighcounter.hpp"
#include "tablenavigator.hpp"

#include "input.hpp"

class View {
public:
    virtual ~View() = default;
    
    // Display for Title
    virtual void displayLayoutTitle() = 0;
    virtual void displayHighlight(const Title::Highlight highlight) = 0;
    
    // Display for Instruction
    virtual void displayLayoutInstruction() = 0;
    
    // Display for Credit
    virtual void displayLayoutCredit() = 0;
    
    // Display for Game Settings
    virtual void displayLayoutGameSettings() = 0;
    virtual void displaySettingsValue(const size_t numOfCoins, const GameLevel level, const bool mode) = 0;
    virtual void displayHighlight(const GameSettings::Highlight highlight) = 0;
    
    // Display for game play
    virtual void displayLayoutGamePlayHuman() = 0;
    virtual void displayLayoutGamePlayComputer() = 0;
    virtual void displayButtonHighlight(const GamePlayHuman::ButtonHighlight highlight) = 0;
    virtual void displayButtonHighlight(const GamePlayComputer::ButtonHighlight highlight) = 0;
    virtual void displayCoinSelection(const CoinSelection &selection, const size_t topRowIndex) = 0;
    virtual void displayWeighResult(const WeighResult weighResult) = 0;
    virtual void displayWeighCounter(const WeighCounter &weighCounter) = 0;
    virtual void displayCoinHighlight(const size_t row, const size_t column) = 0;
    
    // Display for Game Over
    virtual void displayLayoutGameOver(const bool isWin) = 0;
    
    // Information for coin displaying
    virtual const size_t numOfCoinsPerRow() const = 0;
    virtual const size_t numOfRowsPerDisplay() const = 0;
    
    // Input handling functions
    virtual const Input nextInput() = 0;
};

#endif
