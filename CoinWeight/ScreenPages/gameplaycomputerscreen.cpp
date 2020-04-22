//
//  gameplaycomputerscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplaycomputerscreen.hpp"

//************************** Constructor
GamePlayComputerScreen::GamePlayComputerScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const GamePlayComputerScreen::Highlight GamePlayComputerScreen::currHighlight() const {
    return highlight;
}



//************************** Manual highlight switch
void GamePlayComputerScreen::highlightSwitch(const Highlight highlight) {
    this->highlight = highlight;
}



//************************** Reset highlight
void GamePlayComputerScreen::resetHighlight() {
    highlight = defaultHighlight;
}



//************************** Arrow button highlight switch
void GamePlayComputerScreen::highlightUp() {}
void GamePlayComputerScreen::highlightDown() {}
void GamePlayComputerScreen::highlightLeft() {}
void GamePlayComputerScreen::highlightRight() {}
