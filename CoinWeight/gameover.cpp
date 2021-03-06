//
//  gameover.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameover.hpp"
#include "model.hpp"
#include "view.hpp"

using namespace CoinWeight;

//************************** Constructor
GameOver::GameOver(const bool doesPlayerWin) :
playerWin(doesPlayerWin) {}



//************************** Arrow button handling
void GameOver::onArrowUp() {}

void GameOver::onArrowDown() {}

void GameOver::onArrowLeft() {}

void GameOver::onArrowRight() {}



//************************** Character input handling
void GameOver::onCharInput(const char inputChar) {}



//************************** Return button handling
void GameOver::onReturnButton(Model &model) {
    model.switchToTitle();
}



//************************** UI display
void GameOver::triggerDisplay(View &view) {
    view.displayLayoutGameOver(playerWin);
}
