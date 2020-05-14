//
//  gamecontroller.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-29.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecontroller_hpp
#define gamecontroller_hpp

#include <memory>
#include "input.hpp"

class GameModel;
class GameUI;

class GameController {
public:
    GameController();
    void registerModel(const std::shared_ptr<GameModel> model);
    void onReceivingInput(const Input &inp);
    
    // View-related functions
    void updateView(GameUI *view);
    
private:
    std::shared_ptr<GameModel> model;

    // Arrow input handling
    void onScreenArrowInputUp();
    void onScreenArrowInputDown();
    void onScreenArrowInputLeft();
    void onScreenArrowInputRight();
    void onScreenArrowInput(const Input::Arrow arrowInp);
    
    // Character input handling
    void onCharInput0();
    void onCharInput1();
    void onCharInput2();
    void onCharInput3();
    void onReturnButton();
    void onCharInput(const char charInp);
    
    // View update helper functions
    void updateViewTitleScreen(GameUI *view);
    void updateViewInstructionScreen(GameUI *view);
    void updateViewCreditScreen(GameUI *view);
    void updateViewGameOptionScreen(GameUI *view);
    void updateViewGamePlayHumanScreen(GameUI *view);
    void updateViewGamePlayComputerScreen(GameUI *view);
    void updateViewGameOverScreen(GameUI *view);
};

#endif
