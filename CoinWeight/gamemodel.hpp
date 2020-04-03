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
    static const int coinsPerRow = 10;
    
    // Screen transitions helper functions
    void goFromMainScreen();
    void backToMainScreen();
    void gameStart();
    void gameOver();
    void gameCleanUp(); // Clean-up after game over
    
    // Settings manipulation helper functions
    void increaseNumOfCoins();
    void decreaseNumOfCoins();
    void increaseLevel();
    void decreaseLevel();
    void switchMode();
    
    // Computer setup for coin states
    void computerSetup();

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

    void screenTransition();
    
    // Screen highlight manipulation
    void incrementScreenHighlight();
    void decrementScreenHighlight();
    
    // Settings manipulation
    void incrementSettings();
    void decrementSettings();
    
    // Determines if coin highlight is in the corresponding border
    const bool isTopMostCoin() const;
    const bool isBottomMostCoin() const;
    const bool isLeftMostCoin() const;
    const bool isRightMostCoin() const;
    
    // Coin highlight manipulation
    void moveCoinHighlightUp();
    void moveCoinHighlightDown();
    void moveCoinHighlightLeft();
    void moveCoinHighlightRight();
    
    // Coin states manipulation
    void setStateOfCoin(CoinStates::Value state);
    
    // Game operations
    void compareWeight();
    const bool guessFakeCoins() const;
    
    // History index manipulation
    void historyIncrementIndex();
    void historyDecrementIndex();
};



//***************************************************** Game Model Failure
class GameModelFailure : public Exception {
    const std::string headerMessage() const override;
public:
    GameModelFailure(std::string coreMessage);
};

#endif
