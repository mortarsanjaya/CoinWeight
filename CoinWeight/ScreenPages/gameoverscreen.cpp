//
//  gameoverscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameoverscreen.hpp"

//************************** Constructor
GameOverScreen::GameOverScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const GameOverScreen::Highlight GameOverScreen::currHighlight() const {
    return highlight;
}



//************************** Manual highlight switch
void GameOverScreen::highlightSwitch(const Highlight highlight) {
    this->highlight = highlight;
}



//************************** Reset highlight
void GameOverScreen::resetHighlight() {
    highlight = defaultHighlight;
}



//************************** Arrow button highlight switch
void GameOverScreen::highlightUp() {}
void GameOverScreen::highlightDown() {}
void GameOverScreen::highlightLeft() {}
void GameOverScreen::highlightRight() {}
