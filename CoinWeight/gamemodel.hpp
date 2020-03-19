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
#include "input.hpp"
#include "exception.hpp"

class GameModel {
    /*
        Page Transition table:
            Main -> Instruction, Credit, Game Option
            Instruction, Credit -> Main
            Game Option -> Game Play -> Game Over -> Main
    */
    enum class Page {
        Main,
        Instruction,
        Credit,
        GameOption,  // Num of coins, Difficulty, Human/Computer
        GamePlay,    // Coins, just coins, color depends
        GameOver     // You win! You lose!
    };
    
    struct GameSettings {
        size_t numOfCoins;
        GameCore::Level level;
        bool isHuman;
        
        GameSettings(size_t numOfCoins = 13, GameCore::Level level =
            GameCore::Level::Hard, bool isHuman = true);
    };
    
    enum CoinState { NoSelect = 0, Group1 = 1, Group2 = 2 };
    
    std::unique_ptr<GameCore> gameCore;
    std::unique_ptr<Computer> computer;
    Page page;
    std::vector<int> coinStates;
    int pageHighlight;
    GameSettings gameSettings;
    
    /*
        computer is set to NULL if the player is a Human
        pageHighlight:
            If Page is Main or Game Option, either 0, 1, 2 based on
                which button to highlight
            If Page is Game Play, indicates which coin is being highlighted
            If Page is Game Over, 0 indicates loss, 1 indicates win
    */
    
    // Updates game page based on input
    // More documentation on gamemodel.cpp
    void updatePage(char inp);
    void updatePage(Input::Arrow inp);
    
public:
    GameModel();
    
    // Updates the game view
    void updateView(GameView &gameView);
    
    void updatePage(Input inp);
};

class GameModelFailure : public Exception {
    const std::string headerMessage() const override;
public:
    GameModelFailure(std::string coreMessage);
};

#endif
