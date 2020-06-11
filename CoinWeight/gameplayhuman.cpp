//
//  gameplayhuman.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplayhuman.hpp"
#include "model.hpp"
#include "viewx11.hpp"

using namespace CoinWeight;

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
counter(nCoinsTotal, level)
{}



//************************** Private accessor
const size_t GamePlayHuman::coinHighlightIndex() const {
    return coinNavigator.currIndex();
}



//************************** Arrow button handling
//**** Main
void GamePlayHuman::onArrowUp() {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayHuman::onArrowDown() {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayHuman::onArrowLeft() {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayHuman::onArrowRight() {
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
void GamePlayHuman::onReturnButton(Model &model) {
    if (isOnButtonHighlight) {
        switch (buttonHighlight) {
            case ButtonHighlight::Weigh:
            {
                if (counter.isCappedOut()) {
                    lastResult = WeighResult::Invalid;
                } else {
                    lastResult = compareWeight();
                }
                
                if (lastResult != WeighResult::Invalid) {
                    history.add(selection, lastResult);
                    selection.reset();
                    counter.weighingDone();
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
                        model.switchToGameOver(true);
                        break;
                    case GuessResult::Incorrect:
                        model.switchToGameOver(false);
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
void GamePlayHuman::triggerDisplay(ViewX11 &view) const {
    displayLayoutGamePlayHuman(view);
    displayCoinSelection(view);
    displayWeighResult(view);
    displayWeighCounter(view);
    if (isOnButtonHighlight) {
        displayButtonHighlight(view);
    } else {
        displayCoinHighlight(view);
    }
}

void GamePlayHuman::displayLayoutGamePlayHuman(ViewX11 &view) const {
    view.clearWindow();
    view.setForeground(view.defaultFGColor);

    const std::string &weighStr = "Weigh";
    const std::string &guessStr = "Guess";
    
    view.drawString(50 + view.border, 300 + view.total_string_height - view.border, weighStr);
    view.drawString(50 + view.border, 300 + 2 * view.total_string_height - view.border, guessStr);
    
    view.flushDisplay();
}

void GamePlayHuman::displayButtonHighlight(ViewX11 &view) const {
    switch (buttonHighlight) {
        case GamePlayHuman::ButtonHighlight::Weigh:
            view.drawRectangle(50, 300, 40, view.total_string_height);
            break;
        case GamePlayHuman::ButtonHighlight::Guess:
            view.drawRectangle(50, 300 + view.total_string_height, 40, view.total_string_height);
            break;
    }
    
    view.flushDisplay();
}

void GamePlayHuman::displayCoinSelection(ViewX11 &view) const {
    for (size_t row = 0; row < coinNavigator.numOfRowsDisplayed(); ++row) {
        bool coinExhausted = false;
        for (size_t column = 0; column < coinNavigator.numOfColumns(); ++column) {
            const size_t coinIndex = (row + coinNavigator.currTopRow()) * coinNavigator.numOfColumns() + column;
            if (coinIndex >= selection.totalSize()) {
                coinExhausted = true;
                break;
            }
            view.drawCoin(selection.at(coinIndex), coinIndex, row, column);
        }
        
        if (coinExhausted) break;
    }
    
    view.flushDisplay();
}

void GamePlayHuman::displayWeighResult(ViewX11 &view) const {
    view.drawWeighResultText(lastResult);
    view.drawWeighingScale(lastResult);
    
    view.flushDisplay();
}

void GamePlayHuman::displayWeighCounter(ViewX11 &view) const {
    view.setForeground(view.Black);
    std::string numOfWeighsStr = "Number of comparisons done: ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsDone());
    numOfWeighsStr += " out of ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsMax());
    view.drawString(30, 60, numOfWeighsStr);
    
    view.flushDisplay();
}

void GamePlayHuman::displayCoinHighlight(ViewX11 &view) const {
    view.drawRectangle(view.coin0XPos + view.coinDist * coinNavigator.currColumn(), view.coin0YPos + view.coinDist * coinNavigator.currRowDisplay(), view.coinDist, view.coinDist);
    
    view.flushDisplay();
}
