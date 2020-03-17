//
//  gameviewx11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewx11.hpp"
#include <iostream>

GameViewX11::GameViewX11() : coreGraphics{"CoinWeight"} {
    drawMainScreen();
}

//******************************************************************************
void GameViewX11::drawCoin(int x_pos, int y_pos, size_t coinIndex) {
    coreGraphics.drawCircle(x_pos, y_pos, coinRadius, X11Graphics::Black);
    coreGraphics.fillCircle(x_pos, y_pos, coinRadius, X11Graphics::Gold);
    // The index for drawing starts at 1, not 0, to avoid confusion
    coreGraphics.drawString(x_pos, y_pos, std::to_string(coinIndex + 1));
}

void GameViewX11::drawMainScreen() {
    coreGraphics.drawString(200, 200, "Coin Weighting");
    coreGraphics.drawString(200, 300, "Play");
    coreGraphics.drawString(200, 400, "Instructions");
}

void GameViewX11::drawPlayScreen1() {
    coreGraphics.clear();
    coreGraphics.drawString(200, 300, "Enter number of coins: ");
    coreGraphics.drawString(200, 320, "Enter difficulty: ");
    coreGraphics.drawString(200, 340, "Enter mode: ");
    sleep(1);
}

void GameViewX11::drawInstructionScreen() {
    coreGraphics.clear();
    // ...
}

void GameViewX11::drawPlayScreen2(int numOfCoins) {
    coreGraphics.clear();
    coreGraphics.drawString(10, 10, "History");
    
    coreGraphics.drawString(300, 100, "Weigh");
    coreGraphics.drawString(300, 150, "Guess");
    
    for (int i = 0; i < numOfCoins; ++i) {
        drawCoin(200 + 2 * coinRadius * (i % 10), 200 + 2 * coinRadius * (i / 10), i);
    }
    
    sleep(1);
}

