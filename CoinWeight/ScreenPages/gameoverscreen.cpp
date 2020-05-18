//
//  gameoverscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameoverscreen.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Constructor
GameOverScreen::GameOverScreen(const bool doesPlayerWin) :
playerWin(doesPlayerWin) {}



//************************** Field accessor
const bool GameOverScreen::doesPlayerWin() const {
    return playerWin;
}



//************************** Arrow button handling
void GameOverScreen::highlightUp(Controller &controller) {}

void GameOverScreen::highlightDown(Controller &controller) {}

void GameOverScreen::highlightLeft(Controller &controller) {}

void GameOverScreen::highlightRight(Controller &controller) {}



//************************** Character input handling
void GameOverScreen::onCharInput(Controller &controller, const char inputChar) {}



//************************** Return button handling
void GameOverScreen::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void GameOverScreen::triggerDisplay(Controller &controller, View &interface) {
    interface.displayScreen(*this);
}
