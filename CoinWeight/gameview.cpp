//
//  gameview.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameview.hpp"

void GameView::drawCoins(const DrawingWindow drawWindow, const CoinStates &coinStates) {
    for (size_t i = 0; i < coinStates.size(); ++i) {
        drawCoin(drawWindow, coinStates.at(i), i);
    }
}

void GameView::drawRecord(const Record &record) {
    drawCoins(DrawingWindow::History, record.coinStates());
    drawHistoryWeighResultText(record.result());
}

void GameView::drawHistoryScreen(const Record &record, const size_t index) {
    drawRecord(record);
    drawHistoryIndexText(index);
}

void GameView::drawHistoryScreen(const History &history) {
    if (history.empty()) {
        drawEmptyHistoryScreen();
    } else {
        drawHistoryScreen(history.getRecord(), history.currentIndex());
    }
}
