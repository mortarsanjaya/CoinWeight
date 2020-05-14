//
//  gameui.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameui.hpp"

//************************** Destructor
GameUI::~GameUI() {}



//************************** Non-virtual private methods
//**** Draw coins
void GameUI::drawCoins(const CoinSelection &coinStates) {
    for (size_t i = 0; i < coinStates.totalSize(); ++i) {
        drawCoin(coinStates.at(i), i);
    }
}

//**** Draw record
void GameUI::drawRecord(const Record &record) {
    drawCoins(record.coinStates());
    drawWeighResultText(record.result());
}

//**** Draw history screen, non-empty case
/*
void GameUI::drawHistoryScreen(const Record &record,
    const size_t index, const size_t numOfWeighs)
{
    drawRecord(record);
    // drawHistoryIndexText(index, numOfWeighs);
}
*/



//************************** Public methods
void GameUI::drawGamePlayHumanScreen(const CoinSelection &selection, const GamePlayHumanScreen &screen,
const WeighCounter &counter, const WeighResult lastWeighResult) {
    clearScreen();
    drawCoins(selection);
    drawWeighResultText(lastWeighResult);
    drawGamePlayNumOfWeighs(counter);
    drawGamePlayHumanHighlight(screen);
}

void GameUI::drawGamePlayComputerScreen(const CoinSelection &selection, const GamePlayComputerScreen &screen,
const WeighCounter &counter, const WeighResult lastWeighResult) {
    clearScreen();
    drawCoins(selection);
    drawWeighResultText(lastWeighResult);
    drawGamePlayNumOfWeighs(counter);
    drawReturnButton();
}

void GameUI::drawGameOverScreen(const GuessResult guessResult, const WeighCounter &counter)
{
    clearScreen();
    drawGameOverEndMessage(guessResult);
    drawGameOverNumOfWeighs(counter);
}

