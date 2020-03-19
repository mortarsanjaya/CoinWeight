//
//  gamemodel.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-17.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamemodel.hpp"

//***************************************************** Constructor
GameModel::GameModel() : gameCore{}, computer{}, page{Page::Main},
    coinStates{}, pageHighlight{}, gameOption{} {}



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
            if (gameOption == nullptr) throw GameModelFailure{"Game Options failed to initiate."};
            gameView.drawGameOptionScreen(pageHighlight, gameOption->numOfCoins, GameCore::levelToString(gameOption->level), gameOption->isHuman);
            break;
        case Page::GamePlay:
            if (gameCore == nullptr) throw GameModelFailure{"Game failed to initiate."};
            gameView.drawGamePlayScreen(gameCore->numOfCoins(), coinStates, gameCore->gameHistory());
        case Page::GameOver:
            gameView.drawGameOverScreen();
            break;
    }
}



//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
