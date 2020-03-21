//
//  gameviewsdl.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewsdl.hpp"

GameViewSDL::GameViewSDL() : coreGraphics(width, height) {}

void GameViewSDL::drawMainScreen(int screenHighlight) {
    coreGraphics.drawText("Coin Weighting", width/2, 100, 48);
    coreGraphics.drawText("Play", width/2, height/2, 24, screenHighlight == 0 ? true : false);
    coreGraphics.drawText("Instructions", width/2, height/2 + 50, 24, screenHighlight == 1 ? true : false);
    coreGraphics.drawText("Credits", width/2, height/2 + 100, 24, screenHighlight == 2 ? true : false);
}

void GameViewSDL::drawInstructionScreen() {
    // drawText instructions
}

void GameViewSDL::drawCreditScreen() {
    // drawText credits
}

void GameViewSDL::drawGameOptionScreen(
    int screenHighlight, size_t numOfCoins,
    std::string gameLevel,
    bool isHuman) {
    coreGraphics.drawInputBox(
        "Number of Coins:", std::to_string(numOfCoins), width/2, 200, screenHighlight == 0 ? true : false);
    coreGraphics.drawInputBox("Level:", "< " + gameLevel + " >", width/2, 250, screenHighlight == 1 ? true : false);
    coreGraphics.drawButton("Continue", width/2, 300, screenHighlight == 2 ? true : false);
}

void GameViewSDL::drawGamePlayScreen(
    std::vector<int> coinStates,
    int highlightedCoin,
    size_t numOfComparisonsLeft,
    size_t numOfComparisonsCap,
    std::vector<std::pair<Weighing, int>> gameHistory) {
    
}

void GameViewSDL::drawGameOverScreen(
    bool isWin,
    size_t numOfComparisonsLeft,
    size_t numOfComparisonsCap,
    std::vector<size_t> finalGuess) {
    
}

void GameViewSDL::receiveInput() {
    return coreGraphics.receiveInput();
}

const Input GameViewSDL::lastInput() const {
    return coreGraphics.lastInput();
}
