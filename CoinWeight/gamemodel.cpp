//
//  gamemodel.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-17.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamemodel.hpp"
#include "computerhard.hpp"

//***************************************************** Constructor
GameModel::GameModel() : gameCore{}, computer{}, page{Page::Main},
    coinStates{}, pageHighlight{}, gameSettings{} {}
    


//***************************************************** Game Settings Constructor
GameModel::GameSettings::GameSettings(size_t numOfCoins, GameCore::Level level, bool isHuman) :
    numOfCoins{numOfCoins}, level{level}, isHuman{isHuman} {}



//***************************************************** Private methods
/*
    If current page is Main:
        press RETURN to go to page highlighted
    If current page is Instruction or Credit:
        press RETURN to go to Main
    If current page is Game Option:
        press RETURN to start game
        ...
    If current page is Game Play:
        ...
    If current page is Game Over:
        press RETURN to go to Main
*/
void GameModel::updatePage(char inp) {
    switch (page) {
        case Page::Main:
            if (inp == '\n') {
                switch (pageHighlight) {
                    case 0:     page = Page::GameOption;        break;
                    case 1:     page = Page::Instruction;       break;
                    case 2:     page = Page::Credit;            break;
                    default:    throw;
                }
            }
            break;
            
        case Page::Instruction:
        case Page::Credit:
            if (inp == '\n') {
                page = Page::Main;
            }
            break;
            
        case Page::GameOption:
            if (inp == '\n') {
                page = Page::GamePlay;
                gameCore = std::make_unique<GameCore>(gameSettings.numOfCoins, gameSettings.level);
                if (!gameSettings.isHuman) {
                    computer = std::make_unique<ComputerHard>(gameSettings.numOfCoins);
                }
                coinStates = std::vector<int>(gameSettings.numOfCoins, CoinState::NoSelect);
                pageHighlight = 0;
            }
            break;
            
        case Page::GamePlay:
            // ...
            break;
            
        case Page::GameOver:
            if (inp == '\n') {
                page = Page::Main;
                pageHighlight = 0;
                gameCore.reset();
                computer.reset();
                coinStates.clear();
            }
            break;
    }
}



//***************************************************** Public methods
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
            gameView.drawGamePlayScreen(coinStates, gameCore->numOfWeighingsLeft(),
                gameCore->numOfWeighingsCap(), gameCore->gameHistory());
        case Page::GameOver:
            gameView.drawGameOverScreen(pageHighlight, gameCore->numOfWeighingsLeft(),
                gameCore->numOfWeighingsCap());
            break;
    }
}

void GameModel::updatePage(Input inp) {
    switch (inp.inputType()) {
        case Input::Type::Char:     updatePage(inp.whatChar());    break;
        case Input::Type::Arrow:    updatePage(inp.whatArrow());   break;
    }
}



//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
