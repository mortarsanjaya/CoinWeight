//
//  gamemodel.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-17.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamemodel_hpp
#define gamemodel_hpp

#include <memory>
#include "game.hpp"
#include "gameview.hpp"

class GameModel {
public:
    enum class State {
        MainPage,
        InstructionPage,
        CreditPage,
        GamePage
    };
    
private:
    std::unique_ptr<Game> game;
    State state;
    
public:
    GameModel();
    void update(GameView &gameview);
};

#endif
