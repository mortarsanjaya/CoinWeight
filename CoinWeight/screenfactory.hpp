//
//  screenfactory.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef screenfactory_hpp
#define screenfactory_hpp

#include <memory>
#include "gamescreen.hpp"

class ScreenFactory final {
public:
    static std::unique_ptr<GameScreen>
        createTitleScreen();
    
    static std::unique_ptr<GameScreen>
        createInstructionScreen();
        
    static std::unique_ptr<GameScreen>
        createCreditScreen();
        
    static std::unique_ptr<GameScreen>
        createGameSettingsScreen();
        
    static std::unique_ptr<GameScreen>
        createGamePlayHumanScreen(const size_t nCoinsTotal,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);
        
    static std::unique_ptr<GameScreen>
        createGamePlayComputerScreen(const size_t nCoinsTotal,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);
        
    static std::unique_ptr<GameScreen>
        createGameOverScreen(const bool isWin);
};


#endif
