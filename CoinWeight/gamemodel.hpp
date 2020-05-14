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
#include "coingroup.hpp"
#include "coinstates.hpp"
#include "computer.hpp"
#include "history.hpp"
#include "player.hpp"
#include "weighresult.hpp"
#include "guessresult.hpp"

class GameView;

class GameModel {
public:
    GameModel();
    
    const GameScreen::Page currScreen() const;
    const CoinSelection &currentCoinStates() const;
    const bool isHumanMode() const;
    const History &currentHistory() const;
    
    // Game core number of weighings
    const WeighCounter &weighCounter() const;
    
    // Coin states manipulation
    void deselectCoin();
    void moveCoinToLeftGroup();
    void moveCoinToRightGroup();
    void selectCoinToGuess();
    
    // Model logic functions
    void mainScreenOnUpButton();
    void mainScreenOnDownButton();
    void mainScreenOnLeftButton();
    void mainScreenOnRightButton();
    void mainScreenOnReturnButton();
    void historyScreenOnLeftButton();
    void historyScreenOnRightButton();
    
    // View-related functions
    void updateView(GameView *view);

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
    
    // View update helper functions
    void updateViewTitleScreen(GameView *view);
    void updateViewInstructionScreen(GameView *view);
    void updateViewCreditScreen(GameView *view);
    void updateViewGameOptionScreen(GameView *view);
    void updateViewGamePlayHumanScreen(GameView *view);
    void updateViewGamePlayComputerScreen(GameView *view);
    void updateViewGameOverScreen(GameView *view);
};

#endif
