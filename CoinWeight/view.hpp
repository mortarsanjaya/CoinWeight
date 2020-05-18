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
    virtual void displayScreen(const Title &screen) = 0;
    virtual void displayScreen(const Instruction &screen) = 0;
    virtual void displayScreen(const Credit &screen) = 0;
    virtual void displayScreen(const GameSettings &screen) = 0;
    virtual void displayScreen(const GamePlayHuman &screen) = 0;
    virtual void displayScreen(const GamePlayComputer &screen) = 0;
    virtual void displayScreen(const GameOver &screen) = 0;
    
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
