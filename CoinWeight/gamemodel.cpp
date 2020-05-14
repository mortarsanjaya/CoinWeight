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
GameModel::GameModel() : screen(), gameCore(), player(), lastWeighResult(WeighResult::Start), lastGuessResult(GuessResult::Invalid)
{}



//************************** "Field accessors"
const GameScreen::Page GameModel::currScreen() const {
    return screen.currentScreen();
}

const CoinStates &GameModel::currentCoinStates() const {
    return player->currStates();
}

const bool GameModel::isHumanMode() const {
    return player->isHuman();
}

const History &GameModel::currentHistory() const {
    return player->currHistory();
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
        player = std::make_unique<Player>(settings.numOfCoins());
        screen.goToGamePlayHumanScreen(settings.numOfCoins(), coinsPerRow);
    } else {
        player = std::make_unique<Player>(settings.numOfCoins(), settings.gameLevel());
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
    
    const WeighResult weighResult = gameCore->compareWeight(player->currStates());
    lastWeighResult = weighResult;
    if (weighResult == WeighResult::Invalid) return;
    
    player->receiveWeighResult(weighResult);
    screen.resetHighlight();
}

void GameModel::guessFakeCoins() {
    lastGuessResult = gameCore->guessFakeCoins(player->currStates());
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
    if (currScreen() != GameScreen::Page::GamePlayComputer) {
        throw Exception<GameModel>("Computer Game Move Failure: Not a computer game.");
    } else if (player->readyToGuess()) {
        guessFakeCoins();
    } else {
        compareWeight();
    }
}



//************************** History index manipulation
void GameModel::historyIncrementIndex() {
    player->historyIncrementIndex();
}

void GameModel::historyDecrementIndex() {
    player->historyDecrementIndex();
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
    view->drawTitleScreen(screen.titleScreen());
}

void GameModel::updateViewInstructionScreen(GameView *view) {
    view->drawInstructionScreen(screen.instructionScreen());
}

void GameModel::updateViewCreditScreen(GameView *view) {
    view->drawCreditScreen(screen.creditScreen());
}

void GameModel::updateViewGameOptionScreen(GameView *view) {
    view->drawGameOptionScreen(screen.gameOptionScreen());
}

void GameModel::updateViewGamePlayHumanScreen(GameView *view) {
    view->drawGamePlayHumanScreen(player->currStates(),
        screen.gamePlayHumanScreen().currScreenHighlight(),
        screen.gamePlayHumanScreen().currCoinHighlight(),
        gameCore->numOfWeighingsLeft(), gameCore->numOfWeighingsMax(), lastWeighResult);
}

void GameModel::updateViewGamePlayComputerScreen(GameView *view) {
    view->drawGamePlayComputerScreen(player->currStates(), gameCore->numOfWeighingsLeft(),
        gameCore->numOfWeighingsMax(), lastWeighResult);
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
template<> const std::string Exception<GameModel>::headerMessage() const {
    return "Game Model Failure: ";
}
