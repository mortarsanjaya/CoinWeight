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
    void onReceivingInput(GameModel *model, const Input &inp);
    
private:
    // Arrow input handling
    void onScreenArrowInputUp(GameModel *model);
    void onScreenArrowInputDown(GameModel *model);
    void onScreenArrowInputLeft(GameModel *model);
    void onScreenArrowInputRight(GameModel *model);
    void onScreenArrowInput(GameModel *model, const Input::Arrow arrowInp);
    
    // Character input handling
    void onCharInput0(GameModel *model);
    void onCharInput1(GameModel *model);
    void onCharInput2(GameModel *model);
    void onCharInput3(GameModel *model);
    void onReturnButton(GameModel *model);
    void onCharInput(GameModel *model, const char charInp);
    
};

#endif
