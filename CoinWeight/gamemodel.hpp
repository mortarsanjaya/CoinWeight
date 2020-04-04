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
#include "coinstates.hpp"
#include "computer.hpp"
#include "history.hpp"
#include "exception.hpp"

class GameModel {
    GameScreen screen;
    GameSettings settings;
    std::unique_ptr<GameCore> gameCore;
    std::unique_ptr<CoinStates> coinStates;
    std::unique_ptr<Computer> computer;
    int coinHighlight;
    History history;
    
    // Not sure how I should put it right now
    static const int coinsPerRow;
    
    // Screen transition functions
    void goFromMainScreen();
    void goToMainScreen();
    void goToGameOptionScreen();
    void gameStart();
    void gameOver(const bool isWin);
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
    
    // Coin states manipulation
    void setStateOfCoin(CoinStates::Value state);
    
    // Game moves operations
    void compareWeight();
    void guessFakeCoins();
    void humanGameMove();
    void computerGameMove();
    
    // History index manipulation
    void historyIncrementIndex();
    void historyDecrementIndex();
    
public:
    GameModel();
    
    const GameScreen::Page currentScreen() const;
    const int screenHighlight() const;
    const int gameSize() const;
    const GameLevel gameLevel() const;
    const bool isHumanMode() const;
    const CoinStates currentCoinStates() const;
    const bool isComputerReadyToGuess() const;
    const int hightlightedCoinIndex() const;
    const History currentHistory() const;
    // Game core number of weighings
    const size_t numOfWeighingsMax() const;
    const size_t numOfWeighingsLeft() const;
    
    // Coin states manipulation (extension)
    void deselectCoin();
    void moveCoinToLeftGroup();
    void moveCoinToRightGroup();
    void selectCoinToGuess();
    
    // Model logic functions
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void onReturnButton();
};



//***************************************************** Game Model Failure
class GameModelFailure : public Exception {
    const std::string headerMessage() const override;
public:
    GameModelFailure(std::string coreMessage);
};

#endif
