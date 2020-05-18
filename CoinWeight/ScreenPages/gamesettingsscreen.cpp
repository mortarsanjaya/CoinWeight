//
//  gamesettingsscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesettingsscreen.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Static members
size_t GameSettingsScreen::nCoins = defaultNumOfCoins;
GameLevel GameSettingsScreen::level = defaultLevel;
bool GameSettingsScreen::isHuman = defaultIsHuman;


//************************** Constructor
GameSettingsScreen::GameSettingsScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const GameSettingsScreen::Highlight GameSettingsScreen::currHighlight() const {
    return highlight;
}

const size_t GameSettingsScreen::numOfCoins() const {
    return nCoins;
}

const GameLevel GameSettingsScreen::gameLevel() const {
    return level;
}

const bool GameSettingsScreen::isHumanMode() const {
    return isHuman;
}



//************************** Arrow button handling
void GameSettingsScreen::highlightUp() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            break;
        case Highlight::Level:
            highlight = Highlight::NumOfCoins;
            break;
        case Highlight::Mode:
            highlight = Highlight::Level;
            break;
        case Highlight::StartGame:
            highlight = Highlight::Mode;
            break;
        case Highlight::GoBack:
            highlight = Highlight::StartGame;
            break;
    }
}

void GameSettingsScreen::highlightDown() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            highlight = Highlight::Level;
            break;
        case Highlight::Level:
            highlight = Highlight::Mode;
            break;
        case Highlight::Mode:
            highlight = Highlight::StartGame;
            break;
        case Highlight::StartGame:
            highlight = Highlight::GoBack;
            break;
        case Highlight::GoBack:
            break;
    }
}

void GameSettingsScreen::highlightLeft() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            decreaseNumOfCoins();
            break;
        case Highlight::Level:
            decreaseLevel();
            break;
        case Highlight::Mode:
            switchMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}

void GameSettingsScreen::highlightRight() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            increaseNumOfCoins();
            break;
        case Highlight::Level:
            increaseLevel();
            break;
        case Highlight::Mode:
            switchMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}



//************************** Character input handling
void GameSettingsScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void GameSettingsScreen::onReturnButton(Controller &controller) {
    switch (highlight) {
        case Highlight::StartGame:
            controller.switchToGamePlay();
            break;
        case Highlight::GoBack:
            controller.switchToTitle();
            break;
        default:
            break;
    }
}



//************************** UI display
void GameSettingsScreen::triggerDisplay(View &view) {
    view.displayScreen(*this);
    // view.displaySettings(settings);
}



//************************** Member modifier functions
void GameSettingsScreen::increaseNumOfCoins() {
    if (nCoins < numOfCoinsUpperBound) {
        ++nCoins;
    }
}

void GameSettingsScreen::decreaseNumOfCoins() {
    if (nCoins > numOfCoinsLowerBound) {
        --nCoins;
    }
}

void GameSettingsScreen::increaseLevel() {
    switch (level) {
        case GameLevel::Easy:
            level = GameLevel::Medium;
            break;
        case GameLevel::Medium:
            level = GameLevel::Hard;
            break;
        case GameLevel::Hard:
            level = GameLevel::Hard;
            break;
    }
}

void GameSettingsScreen::decreaseLevel() {
    switch (level) {
        case GameLevel::Easy:
            level = GameLevel::Easy;
            break;
        case GameLevel::Medium:
            level = GameLevel::Easy;
            break;
        case GameLevel::Hard:
            level = GameLevel::Medium;
            break;
    }
}

void GameSettingsScreen::switchMode() {
    isHuman = !isHuman;
}
