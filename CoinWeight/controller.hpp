//
//  controller.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef controller_hpp
#define controller_hpp

#include "view.hpp"
#include "modelstate.hpp"

#include "coingroup.hpp"
#include "weighresult.hpp"
#include "gamelevel.hpp"

class Controller final {
public:
    Controller(std::unique_ptr<View> ui);
    
    // Screen switch
    void switchToTitle();
    void switchToInstruction();
    void switchToCredit();
    void switchToGameSettings();
    void switchToGamePlay(const size_t numOfCoins,
        const GameLevel level, const bool isHumanMode);
    void switchToGameOver(const bool isWin);
    
    // Input processing
    void processInput();
    
    // Update display
    void updateDisplay();

private:
    std::unique_ptr<View> ui;
    std::unique_ptr<ModelState> screen;
};

#endif
