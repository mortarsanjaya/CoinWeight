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
void GameView::drawCoins(const CoinSelection &coinStates) {
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
void GameView::drawGamePlayHumanScreen(const CoinSelection &coinStates, const GamePlayHumanScreen &screen,
const WeighCounter &counter, const WeighResult lastWeighResult) {
    clearScreen();
    drawCoins(coinStates);
    drawWeighResultText(lastWeighResult);
    drawGamePlayNumOfWeighs(counter);
    drawGamePlayHumanHighlight(screen);
}

void GameView::drawGamePlayComputerScreen(const CoinSelection &coinStates, const GamePlayComputerScreen &screen,
const WeighCounter &counter, const WeighResult lastWeighResult) {
    clearScreen();
    drawCoins(coinStates);
    drawWeighResultText(lastWeighResult);
    drawGamePlayNumOfWeighs(counter);
    drawReturnButton();
}

void GameView::drawGameOverScreen(const GuessResult guessResult, const WeighCounter &counter)
{
    clearScreen();
    drawGameOverEndMessage(guessResult);
    drawGameOverNumOfWeighs(counter);
}

