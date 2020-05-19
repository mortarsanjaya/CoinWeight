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
#include "computerfactory.hpp"
#include "numofweighsmax.hpp"

//************************** Constructor
GamePlayComputer::GamePlayComputer(const size_t nCoinsTotal, const GameLevel level,
    const size_t nRowsDisplay, const size_t nCoinsPerRow) :
buttonHighlight(ButtonHighlight::NextMove),
coinNavigator(nCoinsTotal, nRowsDisplay, nCoinsPerRow),
isOnButtonHighlight(false),
coinSet(nCoinsTotal),
computer(),
lastResult(WeighResult::Start)
{
    computer = ComputerFactory::create(nCoinsTotal,
        numOfWeighsMax(nCoinsTotal, level), level);
}



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
    return coinNavigator.currRowActual();
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
    if (coinNavigator.currColumn() == 0) {
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
        if (computer->currSelection().sizeOfGuessGroup() == 0) {
            lastResult = coinSet.compareWeight(computer->currSelection());
            computer->receiveWeighResult(lastResult);
        } else {
            const GuessResult result = coinSet.guessFakeCoins(computer->currSelection());
            switch (result) {
                case GuessResult::Invalid:
                    controller.switchToGameOver(false);
                    break;
                case GuessResult::Correct:
                    controller.switchToGameOver(true);
                    break;
                case GuessResult::Incorrect:
                    controller.switchToGameOver(false);
                    break;
            }
        }
    }
}



//************************** UI display
void GamePlayComputer::triggerDisplay(View &view) {
    view.displayScreen(*this);
    view.displayCoinSelection(computer->currSelection(), coinNavigator);
    view.displayWeighResult(lastResult);
    view.displayWeighCounter(computer->weighCounter());
}
