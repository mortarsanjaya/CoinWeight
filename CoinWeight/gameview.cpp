//
//  gameview.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameview.hpp"

//***************************************************** Destructor
GameView::~GameView() {}



//***************************************************** Non-virtual drawing functions
//**** Draw coins
void GameView::drawCoins(const DrawingWindow drawWindow, const CoinStates &coinStates) {
    for (size_t i = 0; i < coinStates.size(); ++i) {
        drawCoin(drawWindow, coinStates.at(i), i);
    }
}

//**** Draw record
void GameView::drawRecord(const Record &record) {
    drawCoins(DrawingWindow::History, record.coinStates());
    drawWeighResultText(DrawingWindow::History, record.result());
}

//**** Draw history screen, non-empty case
void GameView::drawHistoryScreen(const Record &record, const size_t index, const size_t numOfWeighs) {
    drawRecord(record);
    drawHistoryIndexText(index, numOfWeighs);
}

//**** Draw history screen, main function
void GameView::drawHistoryScreen(const History &history) {
    if (history.empty()) {
        drawEmptyHistoryScreen();
    } else {
        drawHistoryScreen(history.getRecord(), history.currentIndex(), history.size());
    }
}
