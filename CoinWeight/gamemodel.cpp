//
//  gamemodel.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-17.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamemodel.hpp"
#include "gameview.hpp"
#include "computerhard.hpp"
#include "computerfactory.hpp"
#include "exception.hpp"
#include <unistd.h>

//************************** Constructor
GameModel::GameModel() : screen(), gameCore(), coinStates(), computer(),
    history(), lastWeighResult(WeighResult::Start), lastGuessResult(GuessResult::Invalid)
{}



//************************** "Field accessors"
const GameScreen::Page GameModel::currScreen() const {
    return screen.currentScreen();
}

const CoinStates &GameModel::currentCoinStates() const {
    return *coinStates;
}

const bool GameModel::isComputerReadyToGuess() const {
    return computer->readyToGuess();
}

const bool GameModel::isHumanMode() const {
    return (!computer);
}

const History &GameModel::currentHistory() const {
    return history;
}

//**** Game core number of weighings
const size_t GameModel::numOfWeighingsMax() const {
    return gameCore->numOfWeighingsMax();
}

const size_t GameModel::numOfWeighingsLeft() const {
    return gameCore->numOfWeighingsLeft();
}



//************************** Screen transition functions
//**** Helper
void GameModel::goFromTitleScreen() {
    if (screen.currentScreen() != GameScreen::Page::Title) {
        throw Exception<GameModel>("Go from title screen: Not a title screen.");
    }
    
    switch (screen.titleHighlight()) {
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
    
    const GameSettings &settings = screen.gameOptionSettings();
    gameCore = std::make_unique<GameCore>(settings.numOfCoins(), settings.gameLevel());
    coinStates = std::make_unique<CoinStates>(settings.numOfCoins());
    if (settings.isHumanMode()) {
        screen.goToGamePlayHumanScreen(settings.numOfCoins(), coinsPerRow);
    } else {
        computer = ComputerFactory::createFactory(settings.gameLevel())->createComputer(settings.numOfCoins());
        screen.goToGamePlayComputerScreen();
        computerSetup();
    }
}

void GameModel::gameOver() {
    screen.goToGameOverScreen();
}

void GameModel::gameCleanUp() {
    gameCore.reset();
    coinStates.reset();
    computer.reset();
    history.clear();
    lastWeighResult = WeighResult::Start;
    lastGuessResult = GuessResult::Invalid;
}

void GameModel::computerSetup() {
    if (isHumanMode()) {
        throw Exception<GameModel>("Not in game play computer mode.");
    }
    
    if (computer->readyToGuess()) {
        *coinStates = computer->pickToGuess();
    } else {
        computer->beforeWeigh();
        *coinStates = computer->pickToWeigh();
    }
}



//************************** Coin states manipulation
void GameModel::deselectCoin() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        coinStates->deselect(screen.gamePlayHumanCoinHighlight());
    }
}

void GameModel::moveCoinToLeftGroup() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        coinStates->moveToLeftWeighGroup(screen.gamePlayHumanCoinHighlight());
    }
}

void GameModel::moveCoinToRightGroup() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        coinStates->moveToRightWeighGroup(screen.gamePlayHumanCoinHighlight());
    }
}

void GameModel::selectCoinToGuess() {
    if (screen.currentScreen() == GameScreen::Page::GamePlayHuman) {
        coinStates->moveToGuessGroup(screen.gamePlayHumanCoinHighlight());
    }
}



//************************** Game moves operations
//**** Title
void GameModel::compareWeight() {
    
    const WeighResult weighResult = gameCore->compareWeight(*coinStates);
    lastWeighResult = weighResult;
    if (weighResult == WeighResult::Invalid) return;
    
    if (!isHumanMode()) {
        computer->afterWeigh(weighResult);
        screen.resetHighlight();
    } else {
        screen.resetHighlight();
    }
    
    history.addRecord(*coinStates, weighResult);
    coinStates->resetStates();
    if (!isHumanMode()) {
        computerSetup();
    }
}

void GameModel::guessFakeCoins() {
    lastGuessResult = gameCore->guessFakeCoins(*coinStates);
    if (lastGuessResult == GuessResult::Invalid) {
        lastWeighResult = WeighResult::Invalid;
    } else {
        gameOver();
    }
}

//**** Extension
void GameModel::humanGameMove() {
    if (currScreen() != GameScreen::Page::GamePlayHuman) {
        throw Exception<GameModel>("Human Game Move Failure: Not a human game.");
    }
    
    switch (screen.gamePlayHumanScreenHighlight()) {
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
    if (currScreen() != GameScreen::Page::GamePlayComputer) {
        throw Exception<GameModel>("Computer Game Move Failure: Not a computer game.");
    } else if (computer->readyToGuess()) {
        guessFakeCoins();
    } else {
        compareWeight();
    }
}



//************************** History index manipulation
void GameModel::historyIncrementIndex() {
    history.incrementIndex();
}

void GameModel::historyDecrementIndex() {
    history.decrementIndex();
}



//************************** Model logic functions
void GameModel::mainScreenOnUpButton() {
    screen.highlightUp();
}

void GameModel::mainScreenOnDownButton() {
    screen.highlightDown();
}

void GameModel::mainScreenOnLeftButton() {
    screen.highlightLeft();
}

void GameModel::mainScreenOnRightButton() {
    screen.highlightRight();
}

void GameModel::mainScreenOnReturnButton() {
    switch (currScreen()) {
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

void GameModel::historyScreenOnLeftButton() {
    historyDecrementIndex();
}

void GameModel::historyScreenOnRightButton() {
    historyIncrementIndex();
}



//************************** View update functions
//**** Helper
void GameModel::updateViewTitleScreen(GameView *view) {
    view->drawTitleScreen(screen.titleHighlight());
}

void GameModel::updateViewInstructionScreen(GameView *view) {
    view->drawInstructionScreen();
}

void GameModel::updateViewCreditScreen(GameView *view) {
    view->drawCreditScreen();
}

void GameModel::updateViewGameOptionScreen(GameView *view) {
    view->drawGameOptionScreen(screen.gameOptionHighlight(), screen.gameOptionSettings());
}

void GameModel::updateViewGamePlayHumanScreen(GameView *view) {
    view->drawGamePlayHumanScreen(*coinStates, screen.gamePlayHumanScreenHighlight(), screen.gamePlayHumanCoinHighlight(),
        gameCore->numOfWeighingsLeft(), gameCore->numOfWeighingsMax(), lastWeighResult);
    view->drawHistoryScreen(history);
}

void GameModel::updateViewGamePlayComputerScreen(GameView *view) {
    view->drawGamePlayComputerScreen(*coinStates, gameCore->numOfWeighingsLeft(),
        gameCore->numOfWeighingsMax(), lastWeighResult);
    view->drawHistoryScreen(history);
}

void GameModel::updateViewGameOverScreen(GameView *view) {
    view->drawGameOverScreen(lastGuessResult,
        gameCore->numOfWeighingsLeft(), gameCore->numOfWeighingsMax());
}

//**** Main
void GameModel::updateView(GameView *view) {
    switch (screen.currentScreen()) {
        case GameScreen::Page::Title:
            updateViewTitleScreen(view);
            break;
        case GameScreen::Page::Instruction:
            updateViewInstructionScreen(view);
            break;
        case GameScreen::Page::Credit:
            updateViewCreditScreen(view);
            break;
        case GameScreen::Page::GameOption:
            updateViewGameOptionScreen(view);
            break;
        case GameScreen::Page::GamePlayHuman:
            updateViewGamePlayHumanScreen(view);
            break;
        case GameScreen::Page::GamePlayComputer:
            updateViewGamePlayComputerScreen(view);
            break;
        case GameScreen::Page::GameOver:
            updateViewGameOverScreen(view);
            break;
    }
}


//************************** Game Model Failure
template<> const std::string exceptionHeaderMessage<GameModel>() {
    return "Game Model Failure: ";
}
