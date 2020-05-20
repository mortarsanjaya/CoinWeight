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
isOnButtonHighlight(true),
coinSet(nCoinsTotal),
selection(nCoinsTotal),
history(),
computer(),
lastResult(WeighResult::Start),
counter(numOfWeighsMax(nCoinsTotal, level))
{
    computer = ComputerFactory::create(nCoinsTotal, level);
    computerSetSelection();
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
        if (selection.sizeOfGuessGroup() == 0) {
            if (counter.isZero()) {
                lastResult = WeighResult::Invalid;
            } else {
                lastResult = compareWeight();
            }
            
            computer->changeState(lastResult);
            selection.reset();
            
            if (lastResult != WeighResult::Invalid) {
                history.add(selection, lastResult);
                counter.decrement();
            }
            
            computerSetSelection();
            
        } else {
            const GuessResult result = guessFakeCoins();
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
//**** Game operations as helper
const WeighResult GamePlayComputer::compareWeight() const {
    return coinSet.compareWeight(selection);
}

const GuessResult GamePlayComputer::guessFakeCoins() const {
    return coinSet.guessFakeCoins(selection);
}



//************************** Computer sets up selection
void GamePlayComputer::computerSetSelection() {
    computer->setSelection(selection);
}



//************************** UI display
void GamePlayComputer::triggerDisplay(View &view) {
    view.displayLayoutGamePlayComputer();
    view.displayCoinSelection(selection, coinNavigator.currTopRow());
    view.displayWeighResult(lastResult);
    view.displayWeighCounter(counter);
    if (isOnButtonHighlight) {
        view.displayButtonHighlight(buttonHighlight);
    } else {
        view.displayCoinHighlight(coinNavigator.currRowDisplay(), coinNavigator.currColumn());
    }
}
