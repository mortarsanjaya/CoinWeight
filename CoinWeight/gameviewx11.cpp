//
//  gameviewx11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewx11.hpp"
#include <iostream>

//***************************************************** Constructor
GameViewX11::GameViewX11() : GameView{}, coreGraphics{"CoinWeight"} {}



//***************************************************** Private methods
void GameViewX11::drawCoin(int coinState, size_t coinIndex) {
    const int x_pos = 50 * (1 + coinIndex % 10);
    const int y_pos = 50 * (1 + coinIndex / 10);
    switch (coinState) {
        case 0: coreGraphics.fillCircle(x_pos, y_pos, coinRadius, X11Graphics::Gold); break;
        case 1: coreGraphics.fillCircle(x_pos, y_pos, coinRadius, X11Graphics::Red); break;
        case 2: coreGraphics.fillCircle(x_pos, y_pos, coinRadius, X11Graphics::Blue); break;
        default: throw;
    }
    coreGraphics.drawCircle(x_pos, y_pos, coinRadius, X11Graphics::Black);
    coreGraphics.drawString(x_pos, y_pos, std::to_string(coinIndex + 1));
}



//***************************************************** Public methods
void GameViewX11::drawMainScreen(int screenHighlight) {
    const int stringHeight = 20;
    coreGraphics.clear();
    
    coreGraphics.drawString(300, 50, "Coin Weight");
    coreGraphics.drawString(300, 300 + stringHeight, "Play");
    coreGraphics.drawString(300, 300 + 2 * stringHeight, "Instructions");
    coreGraphics.drawString(300, 300 + 3 * stringHeight, "Credits");
    
    coreGraphics.drawRectangle(300, 300 + screenHighlight * stringHeight,
        stringHeight, 50);
}

void GameViewX11::drawInstructionScreen() {
    coreGraphics.clear();
    // TO BE FILLED WITH INSTRUCTIONS
    sleep(1);
    coreGraphics.drawString(300, 520, "Return");
    coreGraphics.drawRectangle(300, 500, 20, 50);
}

void GameViewX11::drawCreditScreen() {
    coreGraphics.clear();
    // TO BE FILLED WITH CREDITS
    sleep(1);
    coreGraphics.drawString(300, 520, "Return");
    coreGraphics.drawRectangle(300, 500, 20, 50);
}

void GameViewX11::drawGameOptionScreen(int screenHighlight, size_t numOfCoins,
    std::string gameLevel, bool isHuman)
{
    const int stringHeight = 20;
    coreGraphics.clear();
    
    coreGraphics.drawString(300, 50, "Coin Weight");
    coreGraphics.drawString(300, 300 + stringHeight, "Number of Coins:");
    coreGraphics.drawString(300, 300 + 2 * stringHeight, "Level:");
    coreGraphics.drawString(300, 300 + 3 * stringHeight, "Mode:");
    
    coreGraphics.drawString(400, 300 + stringHeight, std::to_string(numOfCoins));
    coreGraphics.drawString(400, 300 + 2 * stringHeight, gameLevel);
    coreGraphics.drawString(400, 300 + 3 * stringHeight, isHuman ? "Human" : "Computer");
    
    coreGraphics.drawRectangle(400, 300 + screenHighlight * stringHeight,
        stringHeight, 50);
}

void GameViewX11::drawGamePlayScreen(std::vector<int> coinStates,
    std::vector<std::pair<Weighing, int>> gameHistory)
{
    coreGraphics.clear();
    
    for (size_t i = 0; i < coinStates.size(); ++i) {
        drawCoin(coinStates[i], i);
    }
}

void GameViewX11::drawGameOverScreen(bool isWin, int numOfComparisons, int maxNumOfComparisons) {
    coreGraphics.clear();
    
    if (isWin) { coreGraphics.drawString(300, 200, "You Win!"); }
    else { coreGraphics.drawString(300, 200, "You Lose :("); }
    coreGraphics.drawString(300, 300,
        "Number of comparisons: " + std::to_string(numOfComparisons) +
        " out of " + std::to_string(maxNumOfComparisons));
}
