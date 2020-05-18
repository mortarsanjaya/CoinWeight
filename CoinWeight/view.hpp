//
//  view.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef view_hpp
#define view_hpp

#include "titlescreen.hpp"
#include "instructionscreen.hpp"
#include "creditscreen.hpp"
#include "gamesettingsscreen.hpp"
#include "gameplayhumanscreen.hpp"
#include "gameplaycomputerscreen.hpp"
#include "gameoverscreen.hpp"

#include "coinselection.hpp"
#include "weighresult.hpp"
#include "weighcounter.hpp"

#include "input.hpp"

class View {
public:
    virtual ~View() = default;
    
    // Base screen display
    virtual void displayScreen(const TitleScreen &screen) = 0;
    virtual void displayScreen(const InstructionScreen &screen) = 0;
    virtual void displayScreen(const CreditScreen &screen) = 0;
    virtual void displayScreen(const GameSettingsScreen &screen) = 0;
    virtual void displayScreen(const GamePlayHumanScreen &screen) = 0;
    virtual void displayScreen(const GamePlayComputerScreen &screen) = 0;
    virtual void displayScreen(const GameOverScreen &screen) = 0;
    
    // Displaying functions for other elements
    virtual void displayCoinSelection(const CoinSelection &selection) = 0;
    virtual void displayWeighResult(const WeighResult weighResult) = 0;
    virtual void displayWeighCounter(const WeighCounter &weighCounter) = 0;
    
    // Information for coin displaying
    virtual const size_t numOfCoinsPerRow() const = 0;
    virtual const size_t numOfRowsPerDisplay() const = 0;
    
    // Input handling functions
    virtual const Input nextInput() = 0;
};

#endif
