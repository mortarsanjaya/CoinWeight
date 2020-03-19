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
#include "gamecore.hpp"
#include "computer.hpp"
#include "gameview.hpp"

class GameModel {
    enum class Page {
        MainPage,
        InstructionPage,
        CreditPage,
        GameOptionPage,  // Num of coins, Difficulty, Human/Computer
        GamePlayPage,    // Coins, just coins, color depends
        GameOverPage     // You win! You lose!
    };
    
    enum CoinState {
        Scale1 = 0,
        Scale2,
        NotSelected
    };
    
    std::unique_ptr<GameCore> gamecore;
    std::unique_ptr<Computer> computer; // NULL if the player is a human
    Page page;
    std::vector<CoinState> coinStates;  // Selection
    int pageOptionHighlight;
    
public:
    GameModel();
    void updateView(GameView &gameview);
    
    void updatePage(char inp);
};

#endif
