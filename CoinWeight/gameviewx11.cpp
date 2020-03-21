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
    const int x_pos = 200 + 50 * (coinIndex % 10);
    const int y_pos = 200 + 50 * (coinIndex / 10);
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
    
    coreGraphics.drawRectangle(295, 305 + screenHighlight * stringHeight,
        50, stringHeight);
}

void GameViewX11::drawInstructionScreen() {
    coreGraphics.clear();
    // TO BE FILLED WITH INSTRUCTIONS
    sleep(1);
    coreGraphics.drawString(305, 515, "Return");
    coreGraphics.drawRectangle(300, 500, 50, 20);
}

void GameViewX11::drawCreditScreen() {
    coreGraphics.clear();
    // TO BE FILLED WITH CREDITS
    sleep(1);
    coreGraphics.drawString(305, 515, "Return");
    coreGraphics.drawRectangle(300, 500, 50, 20);
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
    
    coreGraphics.drawString(405, 300 + stringHeight, std::to_string(numOfCoins));
    coreGraphics.drawString(405, 300 + 2 * stringHeight, gameLevel);
    coreGraphics.drawString(405, 300 + 3 * stringHeight, isHuman ? "Human" : "Computer");
    
    coreGraphics.drawRectangle(400, 305 + screenHighlight * stringHeight,
        50, stringHeight);
}

void GameViewX11::drawGamePlayScreen(
    std::vector<int> coinStates,
    int highlightedCoin,
    size_t numOfComparisonsLeft,
    size_t numOfComparisonsCap,
    std::vector<std::pair<Weighing, int>> gameHistory)
{
    coreGraphics.clear();
    
    for (size_t i = 0; i < coinStates.size(); ++i) {
        drawCoin(coinStates[i], i);
    }
    
    const std::string numOfCompLeftStr = std::to_string(numOfComparisonsLeft);
    const std::string numOfCompCapStr = std::to_string(numOfComparisonsCap);
    coreGraphics.drawString(30, 30, "Number of comparisons remaining: " + numOfCompLeftStr +
                                    " out of " + numOfCompCapStr);
    if (numOfComparisonsLeft == 0) {
        coreGraphics.drawString(30, 50, "No more comparisons!");
    }
    coreGraphics.drawString(30, 100, "History:");
    const int x_pos = 194 + 50 * (highlightedCoin % 10);
    const int y_pos = 188 + 50 * (highlightedCoin / 10);
    coreGraphics.drawCircle(x_pos, y_pos, 15, coreGraphics.Black);
    
    // HISTORY...
    if (!gameHistory.empty()) {
        coreGraphics.drawString(30, 110, std::to_string(gameHistory.back().second));
    }
}

void GameViewX11::drawGameOverScreen(
    bool isWin,
    size_t numOfComparisonsLeft,
    size_t numOfComparisonsCap,
    std::vector<size_t> finalGuess)
{
    coreGraphics.clear();
    
    if (isWin) { coreGraphics.drawString(300, 200, "You Win!"); }
    else { coreGraphics.drawString(300, 200, "You Lose :("); }
    coreGraphics.drawString(300, 300,
        "Number of comparisons left: " + std::to_string(numOfComparisonsLeft) +
        " out of " + std::to_string(numOfComparisonsCap));
    coreGraphics.drawString(300, 400, "Final guess: ");
    std::string guessStr;
    for (size_t n : finalGuess) {
        guessStr += (std::to_string(n + 1) + " ");
    }
    coreGraphics.drawString(300, 420, guessStr);
}

void GameViewX11::receiveInput() {
    coreGraphics.receiveInput();
}

const Input GameViewX11::lastInput() const {
    XEvent event = coreGraphics.lastInput();
    if (event.type == KeyPress) {
        switch (XLookupKeysym(&event.xkey, 0)) {
            case XK_1:          return Input('1');
            case XK_2:          return Input('2');
            case XK_w:          return Input('w');
            case XK_g:          return Input('g');
            case XK_Return:     return Input('\n');
            case XK_Left:       return Input(Input::Arrow::Left);
            case XK_Right:      return Input(Input::Arrow::Right);
            case XK_Up:         return Input(Input::Arrow::Up);
            case XK_Down:       return Input(Input::Arrow::Down);
            default:            return Input();
        }
    } else {
        return Input();
    }
}
