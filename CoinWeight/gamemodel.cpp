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



//***************************************************** Static constants
const int GameModel::coinsPerRow = 10;



//***************************************************** "Field accessors"
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

const bool GameModel::isComputerReadyToGuess() const {
    return computer->readyToGuess();
}

const int GameModel::hightlightedCoinIndex() const {
    return coinHighlight;
}

const History GameModel::currentHistory() const {
    return history;
}

//**** Game core number of weighings
const size_t GameModel::numOfWeighingsMax() const {
    return gameCore->numOfWeighingsCap();
}

const size_t GameModel::numOfWeighingsLeft() const {
    return gameCore->numOfWeighingsCap();
}



//***************************************************** Screen transition functions
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

void GameModel::goToMainScreen() {
    if (currentScreen() == GameScreen::Page::GameOver) {
        gameCleanUp();
    }
    screen.transition(GameScreen::Page::Main);
}

void GameModel::goToGameOptionScreen() {
    screen.transition(GameScreen::Page::GameOption);
}

void GameModel::gameStart() {
    gameCore = std::make_unique<GameCore>(settings.gameSize(), settings.gameLevel());
    coinStates = std::make_unique<CoinStates>(settings.gameSize());
    if (isHumanMode()) {
        screen.transition(GameScreen::Page::GamePlayHuman);
    } else {
        computer = std::make_unique<ComputerHard>(settings.gameSize());
        screen.transition(GameScreen::Page::GamePlayComputer);
        computerSetup();
    }
}

void GameModel::gameOver(const bool isWin) {
    screen.transition(GameScreen::Page::GameOver);
    if (isWin) {
        coinHighlight = 1;
    } else {
        coinHighlight = 0;
    }
}

void GameModel::gameCleanUp() {
    gameCore.reset();
    coinStates.reset();
    computer.reset();
    history.clear();
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



//***************************************************** Coin highlight check
const bool GameModel::isTopMostCoin() const {
    return (coinHighlight < coinsPerRow);
}

const bool GameModel::isBottomMostCoin() const {
    return (coinHighlight >= gameSize() - coinsPerRow);
}

const bool GameModel::isLeftMostCoin() const {
    return (coinHighlight % coinsPerRow == 0);
}

const bool GameModel::isRightMostCoin() const {
    return (coinHighlight % coinsPerRow == coinsPerRow - 1);
}

const bool GameModel::gamePlayHumanOnCoinHighlight() const {
    return (currentScreen() == GameScreen::Page::GamePlayHuman &&
            screenHighlight() == 0);
}



//***************************************************** Coin highlight manipulation
void GameModel::moveCoinHighlightUp() {
    if (!isTopMostCoin()) {
        coinHighlight -= coinsPerRow;
    }
}

void GameModel::moveCoinHighlightDown() {
    if (!isBottomMostCoin()) {
        coinHighlight += coinsPerRow;
    }
}

void GameModel::moveCoinHighlightLeft() {
    if (!isLeftMostCoin()) {
        --coinHighlight;
    }
}

void GameModel::moveCoinHighlightRight() {
    if (!isRightMostCoin()) {
        ++coinHighlight;
    }
}



//***************************************************** Coin states manipulation
//**** Main
void GameModel::setStateOfCoin(CoinStates::Value state) {
    (*coinStates)[coinHighlight] = state;
}

//**** Extension
void GameModel::deselectCoin() {
    if (currentScreen() == GameScreen::Page::GamePlayHuman) {
        setStateOfCoin(CoinStates::Value::NoSelect);
    }
}

void GameModel::moveCoinToLeftGroup() {
    if (currentScreen() == GameScreen::Page::GamePlayHuman) {
        setStateOfCoin(CoinStates::Value::LeftGroup);
    }
}

void GameModel::moveCoinToRightGroup() {
    if (currentScreen() == GameScreen::Page::GamePlayHuman) {
        setStateOfCoin(CoinStates::Value::RightGroup);
    }
}

void GameModel::selectCoinToGuess() {
    if (currentScreen() == GameScreen::Page::GamePlayHuman) {
        setStateOfCoin(CoinStates::Value::Guess);
    }
}



//***************************************************** Game moves operations
//**** Main
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

void GameModel::guessFakeCoins() {
    bool result = gameCore->guessFakeCoins(*coinStates);
    gameOver(result);
}

//**** Extension
void GameModel::humanGameMove() {
    if (currentScreen() != GameScreen::Page::GamePlayHuman) {
        throw GameModelFailure("Human Game Move Failure: Not a human game.");
    } else {
        switch (screenHighlight()) {
            case 1:
                compareWeight();
                break;
            case 2:
                guessFakeCoins();
                break;
            default:
                break;
        }
    }
}

void GameModel::computerGameMove() {
    if (currentScreen() != GameScreen::Page::GamePlayComputer) {
        throw GameModelFailure("Computer Game Move Failure: Not a computer game.");
    } else {
        if (computer->readyToGuess()) {
            guessFakeCoins();
        } else {
            compareWeight();
        }
    }
}



//***************************************************** History index manipulation
void GameModel::historyIncrementIndex() {
    history.incrementIndex();
}

void GameModel::historyDecrementIndex() {
    history.decrementIndex();
}



//***************************************************** Model logic functions
void GameModel::mainScreenOnUpButton() {
    switch (currentScreen()) {
        case GameScreen::Page::Main:
        case GameScreen::Page::Instruction:
        case GameScreen::Page::Credit:
        case GameScreen::Page::GameOption:
            decrementScreenHighlight();
            break;
        case GameScreen::Page::GamePlayHuman:
            if (gamePlayHumanOnCoinHighlight() && !isTopMostCoin()) {
                moveCoinHighlightUp();
            }
            break;
        case GameScreen::Page::GamePlayComputer:
        case GameScreen::Page::GameOver:
            break;
    }
}

void GameModel::mainScreenOnDownButton() {
    switch (currentScreen()) {
        case GameScreen::Page::Main:
        case GameScreen::Page::Instruction:
        case GameScreen::Page::Credit:
        case GameScreen::Page::GameOption:
            incrementScreenHighlight();
            break;
        case GameScreen::Page::GamePlayHuman:
            if (gamePlayHumanOnCoinHighlight() && !isBottomMostCoin()) {
                moveCoinHighlightDown();
            } else {
                incrementScreenHighlight();
            }
            break;
        case GameScreen::Page::GamePlayComputer:
        case GameScreen::Page::GameOver:
            break;
    }
}

void GameModel::mainScreenOnLeftButton() {
    switch (currentScreen()) {
        case GameScreen::Page::Main:
        case GameScreen::Page::Instruction:
        case GameScreen::Page::Credit:
            break;
        case GameScreen::Page::GameOption:
            decrementSettings();
            break;
        case GameScreen::Page::GamePlayHuman:
            if (gamePlayHumanOnCoinHighlight() && !isLeftMostCoin()) {
                moveCoinHighlightLeft();
            }
            break;
        case GameScreen::Page::GamePlayComputer:
        case GameScreen::Page::GameOver:
            break;
    }
}

void GameModel::mainScreenOnRightButton() {
    switch (currentScreen()) {
        case GameScreen::Page::Main:
        case GameScreen::Page::Instruction:
        case GameScreen::Page::Credit:
            break;
        case GameScreen::Page::GameOption:
            incrementSettings();
            break;
        case GameScreen::Page::GamePlayHuman:
            if (gamePlayHumanOnCoinHighlight() && !isRightMostCoin()) {
                moveCoinHighlightRight();
            }
            break;
        case GameScreen::Page::GamePlayComputer:
        case GameScreen::Page::GameOver:
            break;
    }
}

void GameModel::mainScreenOnReturnButton() {
    switch (currentScreen()) {
        case GameScreen::Page::Main:
            goToGameOptionScreen();
            break;
        case GameScreen::Page::Instruction:
        case GameScreen::Page::Credit:
            goToMainScreen();
            break;
        case GameScreen::Page::GameOption:
            gameStart();
            break;
        case GameScreen::Page::GamePlayHuman:
            humanGameMove();
            break;
        case GameScreen::Page::GamePlayComputer:
            computerGameMove();
            break;
        case GameScreen::Page::GameOver:
            goToMainScreen();
            break;
    }
}

void GameModel::historyScreenOnLeftButton() {
    historyDecrementIndex();
}

void GameModel::historyScreenOnRightButton() {
    historyIncrementIndex();
}



//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
