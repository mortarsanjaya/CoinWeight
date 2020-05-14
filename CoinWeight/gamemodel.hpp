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
#include "gamescreen.hpp"
#include "gamesettings.hpp"
#include "gamecore.hpp"
#include "coinselection.hpp"
#include "computer.hpp"
#include "history.hpp"
#include "player.hpp"
#include "weighresult.hpp"
#include "guessresult.hpp"

class GameUI;

class GameModel {
public:
    GameModel();
    
    const GameScreen &currScreen() const;
    const CoinSelection &currentCoinStates() const;
    const bool isHumanMode() const;
    const History &currentHistory() const;
    
    // PLEASE CLEAN THIS FUNCTION
    const Player *const currPlayer() const;
    const WeighResult prevWeighResult() const;
    const GuessResult prevGuessResult() const;
    
    // Game core number of weighings
    const WeighCounter &weighCounter() const;
    
    // Coin states manipulation
    void deselectCoin();
    void moveCoinToLeftGroup();
    void moveCoinToRightGroup();
    void selectCoinToGuess();
    
    // Model logic functions
    void onUpButton();
    void onDownButton();
    void onLeftButton();
    void onRightButton();
    void onReturnButton();

private:
    GameScreen screen;
    std::unique_ptr<GameCore> gameCore;
    std::unique_ptr<Player> player;
    
    WeighResult lastWeighResult;
    GuessResult lastGuessResult;
    
    static constexpr size_t coinsPerRow = 10;
    
    // Screen transition functions [Might need update]
    void goFromTitleScreen();
    void goToTitleScreen();
    void gameStart();
    void gameOver();
    void gameCleanUp(); // Clean-up after game over
    
    // Game moves operations
    void compareWeight();
    void guessFakeCoins();
    void humanGameMove();
    void computerGameMove();
    
    // History index manipulation
    void historyIncrementIndex();
    void historyDecrementIndex();
};

#endif
