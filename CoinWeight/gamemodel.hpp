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
    
    /*
    enum CoinState {
        NotSelected,
        Scale1,
        Scale2
    };
    */
    
    struct GameOption {
        size_t numOfCoins;
        GameCore::Level level;
        bool isHuman;
    };
    
    std::unique_ptr<GameCore> gameCore;
    std::unique_ptr<Computer> computer; // NULL if the player is a human
    Page page;
    std::vector<int> coinStates;  // Selection
    int pageHighlight;
    std::unique_ptr<GameOption> gameOption;
    
public:
    GameModel();
    void updateView(GameView &gameView);
    
    void updatePage(char inp);
};

class GameModelFailure : public Exception {
    const std::string headerMessage() const override;
public:
    GameModelFailure(std::string coreMessage);
};

#endif
