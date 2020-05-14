//
//  gamemodel.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-17.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamemodel.hpp"
#include "gameui.hpp"
#include "computer.hpp"
#include "playerfactory.hpp"
#include "numofweighsmax.hpp"
#include "exception.hpp"
#include <unistd.h>

//************************** Constructor
GameModel::GameModel() : screen(), gameCore(), player(), lastWeighResult(WeighResult::Start), lastGuessResult(GuessResult::Invalid)
{}



//************************** "Field accessors"
const GameScreen &GameModel::currScreen() const {
    return screen;
}

const CoinSelection &GameModel::currentCoinStates() const {
    return player->currSelection();
}

const bool GameModel::isHumanMode() const {
    return player->isHuman();
}

const History &GameModel::currentHistory() const {
    return player->currHistory();
}

const Player *const GameModel::currPlayer() const {
    return player.get();
}

const WeighResult GameModel::prevWeighResult() const {
    return lastWeighResult;
}

const GuessResult  GameModel::prevGuessResult() const {
    return lastGuessResult;
}


//**** Game core number of weighings
const WeighCounter &GameModel::weighCounter() const {
    return gameCore->weighCounter();
}



//************************** Screen transition functions
//**** Helper
void GameModel::goFromTitleScreen() {
    if (screen.currentScreen() != GameScreen::Page::Title) {
        throw Exception<GameModel>("Go from title screen: Not a title screen.");
    }
    
    switch (screen.titleScreen().currHighlight()) {
        case TitleScreen::Highlight::Play:
            screen.goToGameOptionScreen();
            break;
        case TitleScreen::Highlight::Instruction:
            screen.goToInstructionScreen();
            break;
        case TitleScreen::Highlight::Credit:
            screen.goToCreditScreen();
            break;
    }
}

void GameModel::goToTitleScreen() {
    screen.goToTitleScreen();
}

void GameModel::gameStart() {
    if (screen.currentScreen() != GameScreen::Page::GameOption) {
        throw Exception<GameModel>("Not from game options screen.");
    }
    
    const GameSettings &settings = screen.gameOptionScreen().currSettings();
    gameCore = std::make_unique<GameCore>(settings.numOfCoins(), settings.gameLevel());
    
    if (settings.isHumanMode()) {
        player = PlayerFactory::createHumanStd(settings.numOfCoins(), numOfWeighsMax(settings.numOfCoins(), settings.gameLevel()));
        screen.goToGamePlayHumanScreen(settings.numOfCoins(), coinsPerRow);
    } else {
        player = PlayerFactory::createComputer(settings.numOfCoins(), numOfWeighsMax(settings.numOfCoins(), settings.gameLevel()), settings.gameLevel());
        screen.goToGamePlayComputerScreen();
    }
}

void GameModel::gameOver() {
    screen.goToGameOverScreen();
}

void GameModel::gameCleanUp() {
    gameCore.reset();
    player.reset();
    lastWeighResult = WeighResult::Start;
    lastGuessResult = GuessResult::Invalid;
}



//************************** Coin states manipulation
void GameModel::deselectCoin() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        player->deselectCoin(screen.gamePlayHumanScreen().currCoinHighlight());
    }
}

void GameModel::moveCoinToLeftGroup() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        player->selectCoinToLeftGroup(screen.gamePlayHumanScreen().currCoinHighlight());
    }
}

void GameModel::moveCoinToRightGroup() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        player->selectCoinToRightGroup(screen.gamePlayHumanScreen().currCoinHighlight());
    }
}

void GameModel::selectCoinToGuess() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        player->selectCoinToGuess(screen.gamePlayHumanScreen().currCoinHighlight());
    }
}



//************************** Game moves operations
//**** Title
void GameModel::compareWeight() {
    
    const WeighResult weighResult = gameCore->compareWeight(player->currSelection());
    lastWeighResult = weighResult;
    if (weighResult == WeighResult::Invalid) return;
    
    player->receiveWeighResult(weighResult);
    screen.resetHighlight();
}

void GameModel::guessFakeCoins() {
    lastGuessResult = gameCore->guessFakeCoins(player->currSelection());
    if (lastGuessResult == GuessResult::Invalid) {
        lastWeighResult = WeighResult::Invalid;
    } else {
        gameOver();
    }
}

//**** Extension
void GameModel::humanGameMove() {
    if (currScreen().currentScreen() != GameScreen::Page::GamePlayHuman) {
        throw Exception<GameModel>("Human Game Move Failure: Not a human game.");
    }
    
    switch (screen.gamePlayHumanScreen().currScreenHighlight()) {
        case GamePlayHumanScreen::ScreenHighlight::WeighButton:
            compareWeight();
            break;
        case GamePlayHumanScreen::ScreenHighlight::GuessButton:
            guessFakeCoins();
            break;
        case GamePlayHumanScreen::ScreenHighlight::Coins:
            // ...
            break;
    }
}

void GameModel::computerGameMove() {
    if (currScreen().currentScreen() != GameScreen::Page::GamePlayComputer) {
        throw Exception<GameModel>("Computer Game Move Failure: Not a computer game.");
    } else if (player->currSelection().sizeOfGuessGroup() != 0) {
        guessFakeCoins();
    } else {
        compareWeight();
    }
}



//************************** History index manipulation
/*
void GameModel::historyIncrementIndex() {
    player->historyIncrementIndex();
}

void GameModel::historyDecrementIndex() {
    player->historyDecrementIndex();
}
*/



//************************** Model logic functions
void GameModel::onUpButton() {
    screen.highlightUp();
}

void GameModel::onDownButton() {
    screen.highlightDown();
}

void GameModel::onLeftButton() {
    screen.highlightLeft();
}

void GameModel::onRightButton() {
    screen.highlightRight();
}

void GameModel::onReturnButton() {
    switch (currScreen().currentScreen()) {
        case GameScreen::Page::Title:
            goFromTitleScreen();
            break;
        case GameScreen::Page::Instruction:
            goToTitleScreen();
            break;
        case GameScreen::Page::Credit:
            goToTitleScreen();
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
            gameCleanUp();
            goToTitleScreen();
            break;
    }
}



//************************** Game Model Failure
template<> const std::string Exception<GameModel>::headerMessage() const {
    return "Game Model Failure: ";
}
