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
    const int hightlightedCoinIndex() const;
    const size_t currentHistoryIndex() const;
    const Record currentRecord() const; // Never call when history is empty
    const bool isHistoryEmpty() const;

    void screenTransition();
    
    // Screen highlight manipulation
    void incrementScreenHighlight();
    void decrementScreenHighlight();
    
    // Settings manipulation
    void incrementSettings();
    void decrementSettings();
    
    // Coin highlight manipulation
    // For movng down, delegate to screen highlight move if coin is at bottom row.
    // For moving up, delegate to screen highlight if at either weigh or guess highlight.
    const bool isOnCoinHighlight() const;
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
