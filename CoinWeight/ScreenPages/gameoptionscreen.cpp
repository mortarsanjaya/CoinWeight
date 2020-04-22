//
//  gameoptionscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameoptionscreen.hpp"

//************************** Constructor
GameOptionScreen::GameOptionScreen() : highlight(defaultHighlight),
    settings() {}



//************************** Field accessors
const GameOptionScreen::Highlight GameOptionScreen::currHighlight() const {
    return highlight;
}

const GameSettings &GameOptionScreen::currSettings() const {
    return settings;
}



//************************** Manual highlight switch
void GameOptionScreen::highlightSwitch(const Highlight highlight) {
    this->highlight = highlight;
}


//************************** Reset highlight
void GameOptionScreen::resetHighlight() {
    highlight = defaultHighlight;
}



//************************** Arrow button highlight switch
void GameOptionScreen::highlightUp() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            highlight = Highlight::NumOfCoins;
            break;
        case Highlight::Level:
            highlight = Highlight::NumOfCoins;
            break;
        case Highlight::Mode:
            highlight = Highlight::Level;
            break;
    }
}

void GameOptionScreen::highlightDown() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            highlight = Highlight::Level;
            break;
        case Highlight::Level:
            highlight = Highlight::Mode;
            break;
        case Highlight::Mode:
            highlight = Highlight::Mode;
            break;
    }
}

void GameOptionScreen::highlightLeft() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            settings.decreaseGameSize();
            break;
        case Highlight::Level:
            settings.decreaseDifficulty();
            break;
        case Highlight::Mode:
            settings.switchMode();
            break;
    }
}

void GameOptionScreen::highlightRight() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            settings.increaseGameSize();
            break;
        case Highlight::Level:
            settings.increaseDifficulty();
            break;
        case Highlight::Mode:
            settings.switchMode();
            break;
    }
}
