//
//  gameoverscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameoverscreen.hpp"
#include "gameview.hpp"
#include "gameui.hpp"

//************************** Constructor
GameOverScreen::GameOverScreen(const bool doesPlayerWin) :
playerWin(doesPlayerWin) {}



//************************** Field accessor
const bool GameOverScreen::doesPlayerWin() const {
    return playerWin;
}



//************************** Arrow button handling
void GameOverScreen::highlightUp(GameView &view) {}

void GameOverScreen::highlightDown(GameView &view) {}

void GameOverScreen::highlightLeft(GameView &view) {}

void GameOverScreen::highlightRight(GameView &view) {}



//************************** Character input handling
void GameOverScreen::onCharInput(GameView &view, const char inputChar) {}



//************************** Return button handling
void GameOverScreen::onReturnButton(GameView &view) {
    view.switchToTitle();
}



//************************** UI display
void GameOverScreen::triggerDisplay(GameUI &interface) {
    interface.displayScreen(*this);
}
