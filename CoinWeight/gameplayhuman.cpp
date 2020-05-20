//
//  gameplayhuman.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplayhuman.hpp"
#include "controller.hpp"
#include "view.hpp"
#include "numofweighsmax.hpp"

//************************** Constructor
GamePlayHuman::GamePlayHuman(const size_t nCoinsTotal, const GameLevel level,
    const size_t nRowsDisplay, const size_t nCoinsPerRow) :
buttonHighlight(ButtonHighlight::Weigh),
coinNavigator(nCoinsTotal, nRowsDisplay, nCoinsPerRow),
isOnButtonHighlight(false),
coinSet(nCoinsTotal),
selection(nCoinsTotal),
history(),
lastResult(WeighResult::Start),
counter(numOfWeighsMax(nCoinsTotal, level))
{}



//************************** Private accessor
const size_t GamePlayHuman::coinHighlightIndex() const {
    return coinNavigator.currIndex();
}



//************************** Arrow button handling
//**** Main
void GamePlayHuman::highlightUp() {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayHuman::highlightDown() {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayHuman::highlightLeft() {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayHuman::highlightRight() {
    if (isOnButtonHighlight) {
        buttonHighlightRight();
    } else {
        coinHighlightRight();
    }
}

//**** Helper (button highlight)
void GamePlayHuman::buttonHighlightUp() {
    switch (buttonHighlight) {
        case ButtonHighlight::Weigh:
            break;
        case ButtonHighlight::Guess:
            buttonHighlight = ButtonHighlight::Weigh;
            break;
    }
}

void GamePlayHuman::buttonHighlightDown() {
    switch (buttonHighlight) {
        case ButtonHighlight::Weigh:
            buttonHighlight = ButtonHighlight::Guess;
            break;
        case ButtonHighlight::Guess:
            break;
    }
}

void GamePlayHuman::buttonHighlightLeft() {}

void GamePlayHuman::buttonHighlightRight() {
    transitionToCoinHighlight();
}


//**** Helper (coin highlight)
void GamePlayHuman::coinHighlightUp() {
    coinNavigator.scrollUp();
}

void GamePlayHuman::coinHighlightDown() {
    coinNavigator.scrollDown();
}

void GamePlayHuman::coinHighlightLeft() {
    if (coinNavigator.currColumn() == 0) {
        transitionToButtonHighlight();
    } else {
        coinNavigator.scrollLeft();
    }
}

void GamePlayHuman::coinHighlightRight() {
    coinNavigator.scrollRight();
}

//**** Helper (transition)
void GamePlayHuman::transitionToButtonHighlight() {
    isOnButtonHighlight = true;
}

void GamePlayHuman::transitionToCoinHighlight() {
    isOnButtonHighlight = false;
}



//************************** Character input handling
void GamePlayHuman::onCharInput(const char inputChar) {
    if (!isOnButtonHighlight) {
        switch (inputChar) {
            case '0':
                selection.setGroup(coinHighlightIndex(), CoinGroup::NoSelect);
                break;
            case '1':
                selection.setGroup(coinHighlightIndex(), CoinGroup::LeftWeigh);
                break;
            case '2':
                selection.setGroup(coinHighlightIndex(), CoinGroup::RightWeigh);
                break;
            case '3':
                selection.setGroup(coinHighlightIndex(), CoinGroup::Guess);
                break;
            default:
                break;
        }
    }
}



//************************** Return button handling
void GamePlayHuman::onReturnButton(Controller &controller) {
    if (isOnButtonHighlight) {
        switch (buttonHighlight) {
            case ButtonHighlight::Weigh:
            {
                if (counter.isZero()) {
                    lastResult = WeighResult::Invalid;
                } else {
                    lastResult = compareWeight();
                }
                
                if (lastResult != WeighResult::Invalid) {
                    history.add(selection, lastResult);
                    selection.reset();
                    counter.decrement();
                }
                
                break;
            }
            case ButtonHighlight::Guess:
            {
                switch (guessFakeCoins()) {
                    case GuessResult::Invalid:
                        lastResult = WeighResult::Invalid;
                        break;
                    case GuessResult::Correct:
                        controller.switchToGameOver(true);
                        break;
                    case GuessResult::Incorrect:
                        controller.switchToGameOver(false);
                        break;
                }
                break;
            }
        }
    }
}



//**** Game operations as helper
const WeighResult GamePlayHuman::compareWeight() const {
    return coinSet.compareWeight(selection);
}

const GuessResult GamePlayHuman::guessFakeCoins() const {
    return coinSet.guessFakeCoins(selection);
}



//************************** UI display
void GamePlayHuman::triggerDisplay(View &view) {
    view.displayLayoutGamePlayHuman();
    view.displayCoinSelection(selection, coinNavigator.currTopRow());
    view.displayWeighResult(lastResult);
    view.displayWeighCounter(counter);
    if (isOnButtonHighlight) {
        view.displayButtonHighlight(buttonHighlight);
    } else {
        view.displayCoinHighlight(coinNavigator.currRowDisplay(), coinNavigator.currColumn());
    }
}
