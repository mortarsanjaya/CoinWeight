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

class Controller final {
public:
    Controller(std::unique_ptr<View> ui);
    
    // Screen switch
    void switchToTitle();
    void switchToInstruction();
    void switchToCredit();
    void switchToGameSettings();
    void switchToGamePlay();
    void switchToGameOver(const bool isWin);
    
    // Game-related operations
    void changeCoinGroup(const size_t coinIndex, const CoinGroup newGroup);
    void compareWeight();
    void guessFakeCoins();
    void sendMove();
    
    // Input processing
    void processInput();
    
    // Update display
    void updateDisplay();

private:
    std::unique_ptr<View> ui;
    std::unique_ptr<ModelState> screen;
};

#endif
