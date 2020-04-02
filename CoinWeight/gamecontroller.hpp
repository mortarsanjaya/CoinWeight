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
    void onArrowInputUp();
    void onArrowInputDown();
    void onArrowInputLeft();
    void onArrowInputRight();
    void onArrowInput(Input::Arrow arrowInp);
    
    // Character input handling
    void onCharInput0();
    void onCharInput1();
    void onCharInput2();
    void onCharInput3();
    void onCharInput(char charInp);
    
    // Update view
    void updateView();

public:
    void onReceivingInput(Input inp);
};

#endif
