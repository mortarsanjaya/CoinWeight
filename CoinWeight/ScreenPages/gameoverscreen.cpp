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
void GameOverScreen::highlightUp() {}

void GameOverScreen::highlightDown() {}

void GameOverScreen::highlightLeft() {}

void GameOverScreen::highlightRight() {}



//************************** Character input handling
void GameOverScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void GameOverScreen::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void GameOverScreen::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
