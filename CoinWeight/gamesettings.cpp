//
//  gamesettings.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesettings.hpp"
#include "model.hpp"
#include "viewx11.hpp"

using namespace CoinWeight;

//************************** Static members
size_t GameSettings::nCoins = defaultNumOfCoins;
GameLevel GameSettings::level = defaultLevel;
GameMode GameSettings::mode = defaultMode;



//************************** Constructor
GameSettings::GameSettings() : highlight(defaultHighlight) {}



//************************** Arrow button handling
void GameSettings::onArrowUp() {
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

void GameSettings::onArrowDown() {
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

void GameSettings::onArrowLeft() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            decreaseNumOfCoins();
            break;
        case Highlight::Level:
            decreaseLevel();
            break;
        case Highlight::Mode:
            prevMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}

void GameSettings::onArrowRight() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            increaseNumOfCoins();
            break;
        case Highlight::Level:
            increaseLevel();
            break;
        case Highlight::Mode:
            nextMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}



//************************** Character input handling
void GameSettings::onCharInput(const char inputChar) {}



//************************** Return button handling
void GameSettings::onReturnButton(Model &model) {
    switch (highlight) {
        case Highlight::StartGame:
            model.switchToGamePlay(nCoins, level, mode);
            break;
        case Highlight::GoBack:
            model.switchToTitle();
            break;
        default:
            break;
    }
}



//************************** UI display
void GameSettings::triggerDisplay(ViewX11 &view) {
    view.displayLayoutGameSettings();
    view.displaySettingsValue(nCoins, level, mode);
    view.displayHighlight(highlight);
}



//************************** Member modifier functions
void GameSettings::increaseNumOfCoins() {
    if (nCoins < numOfCoinsUpperBound) {
        ++nCoins;
    }
}

void GameSettings::decreaseNumOfCoins() {
    if (nCoins > numOfCoinsLowerBound) {
        --nCoins;
    }
}

void GameSettings::increaseLevel() {
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

void GameSettings::decreaseLevel() {
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

void GameSettings::nextMode() {
    switch (mode) {
        case GameMode::Standard:
            mode = GameMode::Computer;
            break;
        case GameMode::Computer:
            mode = GameMode::Computer;
            break;
    }
}

void GameSettings::prevMode() {
    switch (mode) {
        case GameMode::Standard:
            mode = GameMode::Standard;
            break;
        case GameMode::Computer:
            mode = GameMode::Standard;
            break;
    }
}
