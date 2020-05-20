//
//  gameover.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameover.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Constructor
GameOver::GameOver(const bool doesPlayerWin) :
playerWin(doesPlayerWin) {}



//************************** Arrow button handling
void GameOver::highlightUp() {}

void GameOver::highlightDown() {}

void GameOver::highlightLeft() {}

void GameOver::highlightRight() {}



//************************** Character input handling
void GameOver::onCharInput(const char inputChar) {}



//************************** Return button handling
void GameOver::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void GameOver::triggerDisplay(View &view) {
    view.displayLayoutGameOver(playerWin);
}
