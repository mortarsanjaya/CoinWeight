//
//  modelstatefactory.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef modelstatefactory_hpp
#define modelstatefactory_hpp

#include <memory>
#include "gamescreen.hpp"
#include "gamelevel.hpp"

namespace CoinWeight {



class ScreenFactory final {
public:
    static std::unique_ptr<GameScreenBase>
        createTitleScreen();
    
    static std::unique_ptr<GameScreenBase>
        createInstructionScreen();
        
    static std::unique_ptr<GameScreenBase>
        createCreditScreen();
        
    static std::unique_ptr<GameScreenBase>
        createGameSettingsScreen();
        
    static std::unique_ptr<GameScreenBase>
        createGamePlayHumanScreen(const size_t nCoinsTotal,
        const GameLevel level);
        
    static std::unique_ptr<GameScreenBase>
        createGamePlayComputerScreen(const size_t nCoinsTotal,
        const GameLevel level);
        
    static std::unique_ptr<GameScreenBase>
        createGameOverScreen(const bool isWin);
};



};

#endif
