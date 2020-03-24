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
GameModel::GameModel() : gameCore{}, computer{}, page{Page::Main},
    coinStates{}, pageHighlight{}, gameSettings{} {}
    


//***************************************************** Game Settings Constructor
GameModel::GameSettings::GameSettings(size_t numOfCoins, GameCore::Level level, bool isHuman) :
    numOfCoins{numOfCoins}, level{level}, isHuman{isHuman} {}



//***************************************************** Private methods
void GameModel::switchFromMainPage() {
    switch (pageHighlight) {
        case 0:     page = Page::GameOption;     break;
        case 1:     page = Page::Instruction;    break;
        case 2:     page = Page::Credit;         break;
    }
}

void GameModel::switchFromInstructionPage() { page = Page::Main; }
void GameModel::switchFromCreditPage() { page = Page::Main; }
void GameModel::switchFromGameOptionPage() {
    page = Page::GamePlay;
    gameCore = std::make_unique<GameCore>(gameSettings.numOfCoins, gameSettings.level);
    if (!gameSettings.isHuman) {
        computer = std::make_unique<ComputerHard>(gameSettings.numOfCoins);
    }
    coinStates = std::vector<int>(gameSettings.numOfCoins, 0);
}

void GameModel::switchFromGamePlayPage() {
    page = Page::GameOver;
}

void GameModel::switchFromGameOverPage() {
    page = Page::Main;
    gameCore.reset();
    computer.reset();
    coinStates.clear();
    pageHighlight = 0;
}

void GameModel::updateMainPage(Input::Arrow inp) {
    switch (inp) {
        case Input::Arrow::Up:
            if (pageHighlight > 0) { --pageHighlight; }
            break;
        case Input::Arrow::Down:
            if (pageHighlight < 2) { ++pageHighlight; }
            break;
        default:
            break;
    }
}

void GameModel::updateGameOptionPage(Input::Arrow inp) {
    switch (inp) {
        case Input::Arrow::Up:
            if (pageHighlight > 0) { --pageHighlight; }
            break;
        case Input::Arrow::Down:
            if (pageHighlight < 2) { ++pageHighlight; }
            break;
        case Input::Arrow::Left:
            switch (pageHighlight) {
                case 0:
                    if (gameSettings.numOfCoins > 2) { --gameSettings.numOfCoins; }
                    break;
                case 1:
                    switch (gameSettings.level) {
                        case GameCore::Level::Easy:
                            gameSettings.level = GameCore::Level::Easy;
                            break;
                        case GameCore::Level::Medium:
                            gameSettings.level = GameCore::Level::Easy;
                            break;
                        case GameCore::Level::Hard:
                            gameSettings.level = GameCore::Level::Medium;
                            break;
                    }
                    break;
                case 2:
                    gameSettings.isHuman = !gameSettings.isHuman;
                    break;
            }
            break;
        case Input::Arrow::Right:
            switch (pageHighlight) {
                case 0:
                    if (gameSettings.numOfCoins < 100) { ++gameSettings.numOfCoins; }
                    break;
                case 1:
                    switch (gameSettings.level) {
                        case GameCore::Level::Easy:
                            gameSettings.level = GameCore::Level::Medium;
                            break;
                        case GameCore::Level::Medium:
                            gameSettings.level = GameCore::Level::Hard;
                            break;
                        case GameCore::Level::Hard:
                            gameSettings.level = GameCore::Level::Hard;
                            break;
                    }
                    break;
                case 2:
                    gameSettings.isHuman = !gameSettings.isHuman;
                    break;
            }
            break;
    }
}

void GameModel::updateGamePlayPage(Input::Arrow inp) {
    const int coinsPerRow = 10;
    switch (inp) {
        case Input::Arrow::Up:
            if (pageHighlight >= coinsPerRow) {
                pageHighlight -= coinsPerRow;
            }
            break;
        case Input::Arrow::Down:
            if (pageHighlight < coinStates.size() - coinsPerRow) {
                pageHighlight += coinsPerRow;
            }
            break;
        case Input::Arrow::Left:
            if (pageHighlight % coinsPerRow > 0) {
                --pageHighlight;
            }
            break;
        case Input::Arrow::Right:
            if (pageHighlight % coinsPerRow < coinsPerRow - 1 && pageHighlight + 1 < coinStates.size()) {
                ++pageHighlight;
            }
            break;
    }
}

void GameModel::updateGamePlayPage(char inp) {
    switch (inp) {
        case '0':
            coinStates[pageHighlight] = CoinState::NoSelect;
            break;
        case '1':
            coinStates[pageHighlight] = CoinState::Group1;
            break;
        case '2':
            coinStates[pageHighlight] = CoinState::Group2;
            break;
        case 'w':
            if (gameCore->numOfWeighingsLeft() != 0) {
                compareWeight();
            }
            break;
        default:
            break;
    }
}



void GameModel::compareWeight() {
    if (computer != nullptr) {
        computer->beforeWeigh();
        const Weighing compWeigh = computer->pickToWeigh();
        for (size_t n : compWeigh.leftGroup) { coinStates[n] = 1; }
        for (size_t n : compWeigh.rightGroup) { coinStates[n] = 2; }
    }
    
    Weighing weighing;
    for (int i = 0; i < coinStates.size(); ++i) {
        if (coinStates[i] == 1) {
            weighing.leftGroup.push_back(i);
        } else if (coinStates[i] == 2) {
            weighing.rightGroup.push_back(i);
        }
        coinStates[i] = 0;
    }
    
    pageHighlight = 0;
    int weighingResult = gameCore->compareWeight(weighing);
    history.emplace_back(weighing, weighingResult);
    if (computer != nullptr) {
        computer->afterWeigh(weighingResult);
    }
}

void GameModel::guessFakeCoins() {
    if (computer != nullptr) {
        const std::vector<size_t> compGuess = computer->pickGuesses();
        for (size_t n : compGuess) { coinStates[n] = 1; }
    }
    
    for (int i = 0; i < coinStates.size(); ++i) {
        if (coinStates[i] == 1) {
            finalGuess.push_back(i);
        }
    }
    
    int guessResult = gameCore->guessFakeCoins(finalGuess);
    pageHighlight = guessResult;
}



//***************************************************** Public methods
const std::vector<Record> GameModel::gameHistory() const {
    return history;
}

void GameModel::updateView(GameView &gameView) {
    switch (page) {
        case Page::Main:
            gameView.drawMainScreen(pageHighlight);
            break;
        case Page::Instruction:
            gameView.drawInstructionScreen();
            break;
        case Page::Credit:
            gameView.drawCreditScreen();
            break;
        case Page::GameOption:
            gameView.drawGameOptionScreen(pageHighlight, gameSettings.numOfCoins,
                GameCore::levelToString(gameSettings.level), gameSettings.isHuman);
            break;
        case Page::GamePlay:
            gameView.drawGamePlayScreen(
                coinStates, pageHighlight,
                gameCore->numOfWeighingsLeft(),
                gameCore->numOfWeighingsCap(),
                gameHistory());
            break;
        case Page::GameOver:
            gameView.drawGameOverScreen(pageHighlight, gameCore->numOfWeighingsLeft(),
                gameCore->numOfWeighingsCap(),
                finalGuess);
            break;
    }
}

void GameModel::processInput(Input inp) {
    switch (page) {
        case Page::Main:
            switch (inp.inputType()) {
                case Input::Type::Char:
                    if (inp.whatChar() == '\n') { switchFromMainPage(); }
                    break;
                case Input::Type::Arrow:
                    updateMainPage(inp.whatArrow());
                    break;
            }
            break;
            
        case Page::Instruction:
            if (inp.inputType() == Input::Type::Char && inp.whatChar() == '\n') {
                switchFromInstructionPage();
            }
            break;
            
        case Page::Credit:
            if (inp.inputType() == Input::Type::Char && inp.whatChar() == '\n') {
                switchFromCreditPage();
            }
            break;
            
        case Page::GameOption:
            switch (inp.inputType()) {
                case Input::Type::Char:
                    if (inp.whatChar() == '\n') { switchFromGameOptionPage(); }
                    break;
                case Input::Type::Arrow:
                    updateGameOptionPage(inp.whatArrow());
                    break;
            }
            break;
            
        case Page::GamePlay:
            if (computer == nullptr) {
                switch (inp.inputType()) {
                    case Input::Type::Char:
                        if (inp.whatChar() == 'g') {
                            guessFakeCoins();
                            switchFromGamePlayPage();
                        } else {
                            updateGamePlayPage(inp.whatChar());
                        }
                        break;
                    case Input::Type::Arrow:
                        updateGamePlayPage(inp.whatArrow());
                        break;
                }
            } else if (inp.inputType() == Input::Type::Char && inp.whatChar() == '\n') {
                if (gameCore->numOfWeighingsLeft() != 0 && !computer->readyToGuess()) {
                    updateGamePlayPage('w');
                } else {
                    guessFakeCoins();
                    switchFromGamePlayPage();
                }
            }
            break;
            
        case Page::GameOver:
            if (inp.inputType() == Input::Type::Char && inp.whatChar() == '\n') {
                switchFromGameOverPage();
            }
            break;
    }
}



//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
