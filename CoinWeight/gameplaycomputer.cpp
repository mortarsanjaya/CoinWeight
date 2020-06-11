//
//  gameplaycomputer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplaycomputer.hpp"
#include "model.hpp"
#include "viewx11.hpp"
#include "computerfactory.hpp"

using namespace CoinWeight;

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
counter(nCoinsTotal, level)
{
    computer = ComputerFactory::create(nCoinsTotal, level);
    computerSetSelection();
}



//************************** Arrow button handling
//**** Main
void GamePlayComputer::onArrowUp() {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayComputer::onArrowDown() {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayComputer::onArrowLeft() {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayComputer::onArrowRight() {
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
void GamePlayComputer::onReturnButton(Model &model) {
    if (isOnButtonHighlight) {
        if (selection.sizeOfGuessGroup() == 0) {
            if (counter.isCappedOut()) {
                lastResult = WeighResult::Invalid;
            } else {
                lastResult = compareWeight();
            }
            
            computer->changeState(lastResult);
            selection.reset();
            
            if (lastResult != WeighResult::Invalid) {
                history.add(selection, lastResult);
                counter.weighingDone();
            }
            
            computerSetSelection();
            
        } else {
            const GuessResult result = guessFakeCoins();
            switch (result) {
                case GuessResult::Invalid:
                    model.switchToGameOver(false);
                    break;
                case GuessResult::Correct:
                    model.switchToGameOver(true);
                    break;
                case GuessResult::Incorrect:
                    model.switchToGameOver(false);
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
void GamePlayComputer::triggerDisplay(ViewX11 &view) const {
    displayLayoutGamePlayComputer(view);
    displayCoinSelection(view, selection, coinNavigator.currTopRow());
    displayWeighResult(view, lastResult);
    displayWeighCounter(view, counter);
    if (isOnButtonHighlight) {
        displayButtonHighlight(view, buttonHighlight);
    } else {
        displayCoinHighlight(view, coinNavigator.currRowDisplay(), coinNavigator.currColumn());
    }
}

void GamePlayComputer::displayLayoutGamePlayComputer(ViewX11 &view) const {
    view.clearWindow();
    view.setForeground(view.defaultFGColor);

    const std::string &nextMoveStr = "Next Move";
    
    view.drawString(50 + view.border, 300 + view.total_string_height - view.border, nextMoveStr);
    
    view.flushDisplay();
}

void GamePlayComputer::displayButtonHighlight(ViewX11 &view, const GamePlayComputer::ButtonHighlight highlight) const {
    switch (highlight) {
        case GamePlayComputer::ButtonHighlight::NextMove:
            view.drawRectangle(50, 300, 64, view.total_string_height);
            break;
    }
    
    view.flushDisplay();
}

void GamePlayComputer::displayCoinSelection(ViewX11 &view, const CoinSelection &selection, const size_t topRowIndex) const {
    for (size_t row = 0; row < coinNavigator.numOfRowsDisplayed(); ++row) {
        bool coinExhausted = false;
        for (size_t column = 0; column < coinNavigator.numOfColumns(); ++column) {
            const size_t coinIndex = (row + topRowIndex) * coinNavigator.numOfColumns() + column;
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

void GamePlayComputer::displayWeighResult(ViewX11 &view, const WeighResult weighResult) const {
    view.drawWeighResultText(weighResult);
    view.drawWeighingScale(weighResult);
    
    view.flushDisplay();
}

void GamePlayComputer::displayWeighCounter(ViewX11 &view, const WeighCounter &counter) const {
    view.setForeground(view.Black);
    std::string numOfWeighsStr = "Number of comparisons done: ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsDone());
    numOfWeighsStr += " out of ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsMax());
    view.drawString(30, 60, numOfWeighsStr);
    
    view.flushDisplay();
}

void GamePlayComputer::displayCoinHighlight(ViewX11 &view, const size_t row, const size_t column) const {
    view.drawRectangle(view.coin0XPos + view.coinDist * column, view.coin0YPos + view.coinDist * row, view.coinDist, view.coinDist);
    
    view.flushDisplay();
}
