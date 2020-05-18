//
//  gameplaycomputer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplaycomputer.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Constructor
GamePlayComputer::GamePlayComputer(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow) :
buttonHighlight(ButtonHighlight::NextMove),
coinNavigator(nCoinsTotal, nRowsDisplay, nCoinsPerRow),
isOnButtonHighlight(false)
{}



//************************** Field accessors
const GamePlayComputer::ButtonHighlight
GamePlayComputer::currButtonHighlight() const {
    return buttonHighlight;
}

const size_t GamePlayComputer::coinDisplayTopRowIndex() const {
    return coinNavigator.currTopRow();
}

const size_t GamePlayComputer::coinHighlightIndex() const {
    return coinNavigator.currIndex();
}

const size_t GamePlayComputer::coinHighlightRow() const {
    return coinNavigator.currRow();
}

const size_t GamePlayComputer::coinHighlightColumn() const {
    return coinNavigator.currColumn();
}

const bool GamePlayComputer::onButtonHighlight() const {
    return isOnButtonHighlight;
}



//************************** Arrow button handling
//**** Main
void GamePlayComputer::highlightUp() {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayComputer::highlightDown() {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayComputer::highlightLeft() {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayComputer::highlightRight() {
    if (isOnButtonHighlight) {
        buttonHighlightRight();
    } else {
        coinHighlightRight();
    }
}

//**** Helper (button highlight)
void GamePlayComputer::buttonHighlightUp() {
}

void GamePlayComputer::buttonHighlightDown() {
}

void GamePlayComputer::buttonHighlightLeft() {}

void GamePlayComputer::buttonHighlightRight() {
    transitionToCoinHighlight();
}


//**** Helper (coin highlight)
void GamePlayComputer::coinHighlightUp() {
    coinNavigator.scrollUp();
}

void GamePlayComputer::coinHighlightDown() {
    coinNavigator.scrollDown();
}

void GamePlayComputer::coinHighlightLeft() {
    if (coinNavigator.currRow() == 0) {
        transitionToButtonHighlight();
    } else {
        coinNavigator.scrollLeft();
    }
}

void GamePlayComputer::coinHighlightRight() {
    coinNavigator.scrollRight();
}

//**** Helper (transition)
void GamePlayComputer::transitionToButtonHighlight() {
    isOnButtonHighlight = true;
}

void GamePlayComputer::transitionToCoinHighlight() {
    isOnButtonHighlight = false;
}



//************************** Character input handling
void GamePlayComputer::onCharInput(const char inputChar) {}



//************************** Return button handling
void GamePlayComputer::onReturnButton(Controller &controller) {
    if (isOnButtonHighlight) {
        controller.sendMove();
    }
}



//************************** UI display
void GamePlayComputer::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
