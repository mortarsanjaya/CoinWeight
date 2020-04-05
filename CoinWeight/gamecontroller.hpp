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
#include "gamemodel.hpp"
#include "gameview.hpp"
#include "input.hpp"

class GameController {
    std::unique_ptr<GameModel> model;
    std::unique_ptr<GameView> view;
    
    // Arrow input handling
    void onMainScreenArrowInputUp();
    void onMainScreenArrowInputDown();
    void onMainScreenArrowInputLeft();
    void onMainScreenArrowInputRight();
    void onMainScreenArrowInput(Input::Arrow arrowInp);
    void onHistoryScreenArrowInputUp();
    void onHistoryScreenArrowInputDown();
    void onHistoryScreenArrowInputLeft();
    void onHistoryScreenArrowInputRight();
    void onHistoryScreenArrowInput(Input::Arrow arrowInp);
    
    // Character input handling (not used by History screen)
    void onCharInput0();
    void onCharInput1();
    void onCharInput2();
    void onCharInput3();
    void onReturnButton();
    void onCharInput(char charInp);
    
    // Update view
    void updateViewOnMainScreen();
    void updateViewOnInstructionScreen();
    void updateViewOnCreditScreen();
    void updateViewOnGameOptionScreen();
    void updateViewOnGamePlayHumanScreen();
    void updateViewOnGamePlayComputerScreen();
    void updateViewOnGameOverScreen();
    

    void onReceivingInput(Input inp);
    
public:
    GameController(GameModel *model, GameView *view);
    void receiveInput();
    void updateView();
};

#endif
