//
//  gameview.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameview.hpp"

//************************** Destructor
GameView::~GameView() {}



//************************** Non-virtual private methods
//**** Draw coins
void GameView::drawCoins(const CoinStates &coinStates) {
    for (size_t i = 0; i < coinStates.totalSize(); ++i) {
        drawCoin(coinStates.at(i), i);
    }
}

//**** Draw record
void GameView::drawRecord(const Record &record) {
    drawCoins(record.coinStates());
    drawWeighResultText(record.result());
}

//**** Draw history screen, non-empty case
void GameView::drawHistoryScreen(const Record &record,
    const size_t index, const size_t numOfWeighs)
{
    drawRecord(record);
    // drawHistoryIndexText(index, numOfWeighs);
}



//************************** Public methods
void GameView::drawGamePlayHumanScreen(const CoinStates &coinStates,
    const GamePlayHumanScreen::ScreenHighlight screenHighlight, const size_t coinHighlight,
    const size_t numOfWeighsLeft, const size_t numOfWeighsMax,
    const WeighResult lastWeighResult)
{
    clearScreen();
    drawCoins(coinStates);
    drawWeighResultText(lastWeighResult);
    drawGamePlayNumOfWeighs(numOfWeighsLeft, numOfWeighsMax);
    drawGamePlayHumanHighlight(screenHighlight, coinHighlight);
}

void GameView::drawGamePlayComputerScreen(const CoinStates &coinStates, const size_t numOfWeighsLeft,
    const size_t numOfWeighsMax, const WeighResult lastWeighResult)
{
    clearScreen();
    drawCoins(coinStates);
    drawWeighResultText(lastWeighResult);
    drawGamePlayNumOfWeighs(numOfWeighsLeft, numOfWeighsMax);
    drawReturnButton();
}

void GameView::drawGameOverScreen(const GuessResult guessResult,
    const size_t numOfWeighsLeft, const size_t numOfWeighMax)
{
    clearScreen();
    drawGameOverEndMessage(guessResult);
    drawGameOverNumOfWeighs(numOfWeighsLeft, numOfWeighMax);
}

