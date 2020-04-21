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
#include "weighresult.hpp"
#include "guessresult.hpp"

class GameView;

class GameModel {
    GameScreen screen;
    GameSettings settings;
    std::unique_ptr<GameCore> gameCore;
    std::unique_ptr<CoinStates> coinStates;
    std::unique_ptr<Computer> computer;
    int coinHighlight;
    History history;
    WeighResult lastWeighResult;
    GuessResult lastGuessResult;
    
    // Not sure how I should put it right now
    static const int coinsPerRow;
    
    // Screen transition functions [Might need update]
    void goFromMainScreen();
    void goToMainScreen();
    void goToGameOptionScreen();
    void gameStart();
    void gameOver();
    void gameCleanUp(); // Clean-up after game over
    void computerSetup(); // Sets up computer for computer game
    
    // Settings manipulation (plus helper functions)
    void increaseNumOfCoins();
    void decreaseNumOfCoins();
    void increaseLevel();
    void decreaseLevel();
    void switchMode();
    void incrementSettings();
    void decrementSettings();
    
    // Screen highlight manipulation
    void incrementScreenHighlight();
    void decrementScreenHighlight();
    
    // Coin highlight check
    const bool isTopMostCoin() const;
    const bool isBottomMostCoin() const;
    const bool isLeftMostCoin() const;
    const bool isRightMostCoin() const;
    const bool gamePlayHumanOnCoinHighlight() const;
    
    // Coin highlight manipulation
    void moveCoinHighlightUp();
    void moveCoinHighlightDown();
    void moveCoinHighlightLeft();
    void moveCoinHighlightRight();
    
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
    
public:
    GameModel();
    
    const GameScreen::Page currentScreen() const;
    const int screenHighlight() const;
    const int gameSize() const;
    const GameLevel gameLevel() const;
    const bool isHumanMode() const;
    const CoinStates currentCoinStates() const;
    const bool isComputerReadyToGuess() const;
    const int highlightedCoinIndex() const;
    const History currentHistory() const;
    // Game core number of weighings
    const size_t numOfWeighingsMax() const;
    const size_t numOfWeighingsLeft() const;
    
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
    
    // View updater functions
    void updateView(GameView *view);
};

#endif
