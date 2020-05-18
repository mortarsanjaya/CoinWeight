//
//  gameplaycomputerscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplaycomputerscreen.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Constructor
GamePlayComputerScreen::GamePlayComputerScreen(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow) :
buttonHighlight(ButtonHighlight::NextMove),
coinNavigator(nCoinsTotal, nRowsDisplay, nCoinsPerRow),
isOnButtonHighlight(false)
{}



//************************** Field accessors
const GamePlayComputerScreen::ButtonHighlight
GamePlayComputerScreen::currButtonHighlight() const {
    return buttonHighlight;
}

const size_t GamePlayComputerScreen::coinDisplayTopRowIndex() const {
    return coinNavigator.currTopRow();
}

const size_t GamePlayComputerScreen::coinHighlightIndex() const {
    return coinNavigator.currIndex();
}

const size_t GamePlayComputerScreen::coinHighlightRow() const {
    return coinNavigator.currRow();
}

const size_t GamePlayComputerScreen::coinHighlightColumn() const {
    return coinNavigator.currColumn();
}

const bool GamePlayComputerScreen::onButtonHighlight() const {
    return isOnButtonHighlight;
}



//************************** Arrow button handling
//**** Main
void GamePlayComputerScreen::highlightUp(Controller &controller) {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayComputerScreen::highlightDown(Controller &controller) {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayComputerScreen::highlightLeft(Controller &controller) {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayComputerScreen::highlightRight(Controller &controller) {
    if (isOnButtonHighlight) {
        buttonHighlightRight();
    } else {
        coinHighlightRight();
    }
}

//**** Helper (button highlight)
void GamePlayComputerScreen::buttonHighlightUp() {
}

void GamePlayComputerScreen::buttonHighlightDown() {
}

void GamePlayComputerScreen::buttonHighlightLeft() {}

void GamePlayComputerScreen::buttonHighlightRight() {
    transitionToCoinHighlight();
}


//**** Helper (coin highlight)
void GamePlayComputerScreen::coinHighlightUp() {
    coinNavigator.scrollUp();
}

void GamePlayComputerScreen::coinHighlightDown() {
    coinNavigator.scrollDown();
}

void GamePlayComputerScreen::coinHighlightLeft() {
    if (coinNavigator.currRow() == 0) {
        transitionToButtonHighlight();
    } else {
        coinNavigator.scrollLeft();
    }
}

void GamePlayComputerScreen::coinHighlightRight() {
    coinNavigator.scrollRight();
}

//**** Helper (transition)
void GamePlayComputerScreen::transitionToButtonHighlight() {
    isOnButtonHighlight = true;
}

void GamePlayComputerScreen::transitionToCoinHighlight() {
    isOnButtonHighlight = false;
}



//************************** Character input handling
void GamePlayComputerScreen::onCharInput(Controller &controller, const char inputChar) {}



//************************** Return button handling
void GamePlayComputerScreen::onReturnButton(Controller &controller) {
    if (isOnButtonHighlight) {
        controller.sendMove();
    }
}



//************************** UI display
void GamePlayComputerScreen::triggerDisplay(Controller &controller, View &interface) {
    interface.displayScreen(*this);
}
