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

    // Arrow input handling
    void onMainScreenArrowInputUp(GameModel *model);
    void onMainScreenArrowInputDown(GameModel *model);
    void onMainScreenArrowInputLeft(GameModel *model);
    void onMainScreenArrowInputRight(GameModel *model);
    void onMainScreenArrowInput(GameModel *model, const Input::Arrow arrowInp);
    void onHistoryScreenArrowInputUp(GameModel *model);
    void onHistoryScreenArrowInputDown(GameModel *model);
    void onHistoryScreenArrowInputLeft(GameModel *model);
    void onHistoryScreenArrowInputRight(GameModel *model);
    void onHistoryScreenArrowInput(GameModel *model, const Input::Arrow arrowInp);
    
    // Character input handling (not used by History screen)
    void onCharInput0(GameModel *model);
    void onCharInput1(GameModel *model);
    void onCharInput2(GameModel *model);
    void onCharInput3(GameModel *model);
    void onReturnButton(GameModel *model);
    void onCharInput(GameModel *model, const char charInp);
    
public:
    GameController();
    void onReceivingInput(GameModel *model, const Input &inp);
};

#endif
