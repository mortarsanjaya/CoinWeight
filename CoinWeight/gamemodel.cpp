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
            gameView.drawGameOptionScreen(pageHighlight, gameOption->numOfCoins,
                GameCore::levelToString(gameOption->level), gameOption->isHuman);
            break;
        case Page::GamePlay:
            if (gameCore == nullptr) throw GameModelFailure{"Game failed to initiate."};
            gameView.drawGamePlayScreen(coinStates, gameCore->numOfWeighingsLeft(),
                gameCore->numOfWeighingsCap(), gameCore->gameHistory());
        case Page::GameOver:
            gameView.drawGameOverScreen(pageHighlight, gameCore->numOfWeighingsLeft(), gameCore->numOfWeighingsCap());
            break;
    }
}

/*
    If current page is Main:
        press RETURN to go to page highlighted
    If current page is Instruction or Credit:
        press RETURN to return to Main
    If current page is Game Option:
        press RETURN to start game
    If current page is Game Play:
        ...
*/
void GameModel::updatePage(char inp) {
    switch (page) {
        case Page::Main:
            if (inp == '\n') {
            
            }
            break;
            
        case Page::Instruction:
        case Page::Credit:
            if (inp == '\n') {
                page = Page::Main;
                pageHighlight = 0;
            }
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
        
        
            
        case Page::GameOption:
            if (inp == '\n') {
                
            }
            break;
            
        case Page::GamePlay:
            // ...
            break;
    }
}



//***************************************************** Public methods




//***************************************************** Game Model Failure
GameModelFailure::GameModelFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string GameModelFailure::headerMessage() const {
    return "Game Model Failure: ";
}
