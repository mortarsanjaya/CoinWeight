//
//  gameoverscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameoverscreen.hpp"
#include "gamecontroller.hpp"
#include "gameui.hpp"

//************************** Constructor
GameOverScreen::GameOverScreen(const bool doesPlayerWin) :
playerWin(doesPlayerWin) {}



//************************** Field accessor
const bool GameOverScreen::doesPlayerWin() const {
    return playerWin;
}



//************************** Arrow button handling
void GameOverScreen::highlightUp(GameController &controller) {}

void GameOverScreen::highlightDown(GameController &controller) {}

void GameOverScreen::highlightLeft(GameController &controller) {}

void GameOverScreen::highlightRight(GameController &controller) {}



//************************** Character input handling
void GameOverScreen::onCharInput(GameController &controller, const char inputChar) {}



//************************** Return button handling
void GameOverScreen::onReturnButton(GameController &controller) {
    controller.switchToTitle();
}



//************************** UI display
void GameOverScreen::triggerDisplay(GameController &controller, GameUI &interface) {
    interface.displayScreen(*this);
}
