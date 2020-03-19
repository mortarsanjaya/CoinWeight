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
    Page page;
    std::vector<int> coinStates;
    int pageHighlight;
    std::unique_ptr<GameOption> gameOption;
    
    /*
        computer is set to NULL if the player is a Human
        coinStates: a coin's state is:
            0, if it is not in any group
            1, if it is in group 1
            2, if it is in group 2
        pageHighlight:
            If Page is Main or Game Option, either 0, 1, 2 based on
                which button to highlight
            If Page is Game Play, indicates which coin is being highlighted
            If Page is Game Over, 0 indicates loss, 1 indicate win
    */
    
    
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
