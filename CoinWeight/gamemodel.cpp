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
void GameModel::updateFromMainPage(Input inp) {
    
}

void GameModel::updateFromInstructionPage(Input inp) {

}

void GameModel::updateFromCreditPage(Input inp) {
    
}

void GameModel::updateFromGameOptionPage(Input inp) {
    
}

void GameModel::updateFromGamePlayPage(Input inp) {

}

void GameModel::updateFromGameOverPage(Input inp) {
    if (inp.inputType() == Input::Type::Char && inp.whatChar() == '\n') {
        page = Page::Main;
        gameCore.reset();
        computer.reset();
        coinStates.clear();
        pageHighlight = 0;
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
            break;
        case Page::GameOver:
            gameView.drawGameOverScreen(pageHighlight, gameCore->numOfWeighingsLeft(),
                gameCore->numOfWeighingsCap());
            break;
    }
}

void GameModel::updatePage(Input inp) {
    switch (page) {
        case Page::Main:            updateFromMainPage(inp);           break;
        case Page::Instruction:     updateFromInstructionPage(inp);    break;
        case Page::Credit:          updateFromCreditPage(inp);         break;
        case Page::GameOption:      updateFromGameOptionPage(inp);     break;
        case Page::GamePlay:        updateFromGamePlayPage(inp);       break;
        case Page::GameOver:        updateFromGameOverPage(inp);       break;
    }
}



//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
