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
#include "player.hpp"
#include "gameview.hpp"

class GameModel {
    enum class Page {
        MainPage,
        InstructionPage,
        CreditPage,
        OptionSelectPage,   // Num of coins, Difficulty, Human/Computer
        GamePage,           // Coins, just coins, color depends
        EndScreenPage       // You win! You lose!
    };
    
    enum class CoinState {
        Scale1,
        Scale2,
        NotSelected
    };
    
    std::unique_ptr<Game> game;
    Page page;
    std::vector<CoinState> coinStates;  // Selection
    int pageOptionHighlight;
    
    
public:
    GameModel();
    void update(GameView &gameview);
};

#endif
