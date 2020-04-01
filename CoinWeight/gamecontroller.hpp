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

class GameController {
    std::unique_ptr<GameModel> model;
    std::unique_ptr<GameView> view;
    
    // Arrow input handling
    void onArrowInputUp();
    void onArrowInputDown();
    void onArrowInputLeft();
    void onArrowInputRight();

public:
    GameController();
};

#endif
