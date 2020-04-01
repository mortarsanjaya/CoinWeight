//
//  gamemodel.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-17.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamemodel.hpp"
#include "computerhard.hpp"
#include <unistd.h>

//***************************************************** Constructor
GameModel::GameModel() :
    screen(), settings(), gameCore(), coinStates(),
    computer(), coinHighlight(), history() {}



//***************************************************** Field accessors
const GameScreen::Page GameModel::currentScreen() const {
    return screen.currentScreen();
}

const int GameModel::screenHighlight() const {
    return screen.currentHighlight();
}

const int GameModel::gameSize() const {
    return settings.gameSize();
}

const GameLevel GameModel::gameLevel() const {
    return settings.gameLevel();
}

const bool GameModel::isHumanMode() const {
    return settings.isHumanMode();
}

const CoinStates GameModel::currentCoinStates() const {
    return *coinStates;
}

const int GameModel::hightlightedCoinIndex() const {
    return coinHighlight;
}

const size_t GameModel::currentHistoryIndex() const {
    return history.currentIndex();
}

const Record GameModel::currentRecord() const {
    return history.getRecord();
}

const bool GameModel::isHistoryEmpty() const {
    return history.empty();
}



//***************************************************** Screen transitions
//**** Helper
void GameModel::goFromMainScreen() {
    switch (screenHighlight()) {
        case 0:
            screen.transition(GameScreen::Page::GameOption);
            break;
        case 1:
            screen.transition(GameScreen::Page::Instruction);
            break;
        case 2:
            screen.transition(GameScreen::Page::Credit);
            break;
        default:
            throw GameModelFailure("Game Screen Highlight out of range.");
    }
}

void GameModel::backToMainScreen() {
    screen.transition(GameScreen::Page::Main);
}

void GameModel::gameStart() {
    gameCore = std::make_unique<GameCore>(settings.gameSize(), settings.gameLevel());
    coinStates = std::make_unique<CoinStates>(settings.gameSize());
    if (isHumanMode()) {
        screen.transition(GameScreen::Page::GamePlayHuman);
    } else {
        computer = std::make_unique<ComputerHard>(settings.gameSize());
        screen.transition(GameScreen::Page::GamePlayComputer);
    }
}

void GameModel::gameOver() {
    screen.transition(GameScreen::Page::GameOver);
    coinHighlight = 0;
}

//**** Main
void GameModel::screenTransition() {
    switch (currentScreen()) {
        case GameScreen::Page::Main:
            goFromMainScreen();
            break;
        case GameScreen::Page::Instruction:
        case GameScreen::Page::Credit:
            backToMainScreen();
            break;
        case GameScreen::Page::GameOption:
            gameStart();
            break;
        case GameScreen::Page::GamePlayHuman:
        case GameScreen::Page::GamePlayComputer:
            gameOver();
            break;
        case GameScreen::Page::GameOver:
            gameCleanUp();
            backToMainScreen();
            break;
    }
}

void GameModel::gameCleanUp() {
    gameCore.reset();
    coinStates.reset();
    computer.reset();
    history.clear();
}



//***************************************************** Screen highlight manipulation
void GameModel::incrementScreenHighlight() {
    screen.incrementHighlight();
}

void GameModel::decrementScreenHighlight() {
    screen.decrementHighlight();
}



//***************************************************** Settings manipulation
//**** Helper
void GameModel::increaseNumOfCoins() {
    settings.increaseGameSize();
}

void GameModel::decreaseNumOfCoins() {
    settings.decreaseGameSize();
}

void GameModel::increaseLevel() {
    settings.increaseDifficulty();
}

void GameModel::decreaseLevel() {
    settings.decreaseDifficulty();
}

void GameModel::switchMode() {
    settings.switchMode();
}

//**** Main
void GameModel::incrementSettings() {
    switch (screenHighlight()) {
        case 0:
            increaseNumOfCoins();
            break;
        case 1:
            increaseLevel();
            break;
        case 2:
            switchMode();
            break;
        default:
            throw GameModelFailure("Game Screen Highlight out of range.");
    }
}

void GameModel::decrementSettings() {
    switch (screenHighlight()) {
        case 0:
            decreaseNumOfCoins();
            break;
        case 1:
            decreaseLevel();
            break;
        case 2:
            switchMode();
            break;
        default:
            throw GameModelFailure("Game Screen Highlight out of range.");
    }
}



//***************************************************** Coin highlight manipulation
const bool GameModel::isOnCoinHighlight() const {
    if (currentScreen() != GameScreen::Page::GamePlayHuman) {
        return false;
    } else {
        return (screenHighlight() == 0);
    }
}

void GameModel::moveCoinHighlightUp() {
    if (screenHighlight() != 0) {
        decrementScreenHighlight();
    } else if (coinHighlight >= coinsPerRow) {
        coinHighlight -= coinsPerRow;
    }
}

void GameModel::moveCoinHighlightDown() {
    if (coinHighlight < gameSize() - coinsPerRow) {
        coinHighlight += coinsPerRow;
    } else {
        incrementScreenHighlight();
    }
}

void GameModel::moveCoinHighlightLeft() {
    if (coinHighlight % coinsPerRow > 0) {
        --coinHighlight;
    }
}

void GameModel::moveCoinHighlightRight() {
    if (coinHighlight % coinsPerRow < coinsPerRow - 1) {
        ++coinHighlight;
    }
}



//***************************************************** Coin states manipulation
void GameModel::setStateOfCoin(CoinStates::Value state) {
    (*coinStates)[coinHighlight] = state;
}

void GameModel::computerSetup() {
    if (isHumanMode()) {
        throw GameModelFailure("Computer setup failed: Not computer mode.");
    }
    
    if (computer->readyToGuess()) {
        *coinStates = computer->pickToGuess();
    } else {
        computer->beforeWeigh();
        *coinStates = computer->pickToWeigh();
    }
}



//***************************************************** Game operations
void GameModel::compareWeight() {
    const WeighResult weighResult = gameCore->compareWeight(*coinStates);
    if (!isHumanMode()) {
        computer->afterWeigh(weighResult);
    }
    coinStates->resetStates();
    coinHighlight = 0;
    history.addRecord(*coinStates, weighResult);
    if (!isHumanMode()) {
        computerSetup();
    }
}

const bool GameModel::guessFakeCoins() const {
    return gameCore->guessFakeCoins(*coinStates);
}



//***************************************************** History index manipulation
void GameModel::historyIncrementIndex() {
    history.incrementIndex();
}

void GameModel::historyDecrementIndex() {
    history.decrementIndex();
}



//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
