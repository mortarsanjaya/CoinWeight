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
#include "exception.hpp"

class GameModel {
    enum class Page {
        Main,
        Instruction,
        Credit,
        GameOption,  // Num of coins, Difficulty, Human/Computer
        GamePlay,    // Coins, just coins, color depends
        GameOver     // You win! You lose!
    };
    
    struct GameOption {
        size_t numOfCoins;
        GameCore::Level level;
        bool isHuman;
    };
    
    std::unique_ptr<GameCore> gameCore;
    std::unique_ptr<Computer> computer;
    // NULL if the player is a human
    Page page;
    /*
        State for selection:
        0 for no select
        1 for group 1
        2 for group 2
    */
    std::vector<int> coinStates;
    /* For Game Over Page: 0 if lose, 1 if win */
    int pageHighlight;
    std::unique_ptr<GameOption> gameOption;
    
    
    
public:
    GameModel();
    
    enum class KeyboardArrowInput {
        Up,
        Down,
        Left,
        Right
    };
    
    // Updates the game view
    void updateView(GameView &gameView);
    
    // Updates game page based on input
    // More documentation on gamemodel.cpp
    void updatePage(char inp);
    void updatePage(KeyboardArrowInput inp);
};

class GameModelFailure : public Exception {
    const std::string headerMessage() const override;
public:
    GameModelFailure(std::string coreMessage);
};

#endif
