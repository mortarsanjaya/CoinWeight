//
//  gameplayhumanscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplayhumanscreen.hpp"

//************************** Constructor
GamePlayHumanScreen::GamePlayHumanScreen(size_t numOfCoins, size_t coinsPerRow) :
    screenHighlight(defaultScreenHighlight), numOfCoins(numOfCoins),
    coinsPerRow(coinsPerRow), coinHighlight(defaultCoinHighlight)
{}



//************************** Move assignment operator have to be defined
GamePlayHumanScreen &GamePlayHumanScreen::operator=(GamePlayHumanScreen &&other) {
    screenHighlight = other.screenHighlight;
    const_cast<size_t &>(numOfCoins) = other.numOfCoins;
    const_cast<size_t &>(coinsPerRow) = other.coinsPerRow;
    coinHighlight = other.coinHighlight;
    return *this;
}
    


//************************** Field accessors
const GamePlayHumanScreen::ScreenHighlight GamePlayHumanScreen::currScreenHighlight() const {
    return screenHighlight;
}

const size_t GamePlayHumanScreen::currCoinHighlight() const {
    return coinHighlight;
}



//************************** Manual highlight switch
void GamePlayHumanScreen::screenHighlightSwitch(const ScreenHighlight screenHighlight) {
    this->screenHighlight = screenHighlight;
}

void GamePlayHumanScreen::coinHighlightSwitch(const size_t coinHighlight) {
    this->coinHighlight = coinHighlight;
}



//************************** Reset highlight
void GamePlayHumanScreen::resetHighlight() {
    screenHighlight = defaultScreenHighlight;
    coinHighlight = defaultCoinHighlight;
}



//************************** Arrow button highlight switch
void GamePlayHumanScreen::highlightUp() {
     switch (screenHighlight) {
         case ScreenHighlight::WeighButton:
             screenHighlightSwitch(ScreenHighlight::WeighButton);
             break;
         case ScreenHighlight::GuessButton:
             screenHighlightSwitch(ScreenHighlight::WeighButton);
             break;
         case ScreenHighlight::Coins:
             highlightUpAtCoins();
             break;
     }
}

void GamePlayHumanScreen::highlightDown() {
     switch (screenHighlight) {
         case ScreenHighlight::WeighButton:
             screenHighlightSwitch(ScreenHighlight::GuessButton);
             break;
         case ScreenHighlight::GuessButton:
             screenHighlightSwitch(ScreenHighlight::Coins);
             break;
         case ScreenHighlight::Coins:
             highlightDownAtCoins();
             break;
     }
}

void GamePlayHumanScreen::highlightLeft() {
     if (screenHighlight == ScreenHighlight::Coins) {
        highlightLeftAtCoins();
     }
}

void GamePlayHumanScreen::highlightRight() {
     if (screenHighlight == ScreenHighlight::Coins) {
        highlightRightAtCoins();
     }
}



//************************** Arrow button highlight switch at Coins
void GamePlayHumanScreen::highlightUpAtCoins() {
    if (coinHighlight < coinsPerRow) {
        screenHighlightSwitch(ScreenHighlight::GuessButton);
    } else {
        coinHighlight -= coinsPerRow;
    }
}

void GamePlayHumanScreen::highlightDownAtCoins() {
    if (coinHighlight + coinsPerRow < numOfCoins) {
        coinHighlight += coinsPerRow;
    }
}

void GamePlayHumanScreen::highlightLeftAtCoins() {
    if (coinHighlight % coinsPerRow != 0) {
        --coinHighlight;
    }
}

void GamePlayHumanScreen::highlightRightAtCoins() {
    if ((coinHighlight % coinsPerRow < coinsPerRow - 1) && (coinHighlight < numOfCoins - 1)) {
        ++coinHighlight;
    }
}
