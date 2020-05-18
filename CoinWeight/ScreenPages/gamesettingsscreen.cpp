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

//************************** Settings
GameSettings GameSettingsScreen::settings {};



//************************** Constructor
GameSettingsScreen::GameSettingsScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const GameSettingsScreen::Highlight GameSettingsScreen::currHighlight() const {
    return highlight;
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
            settings.decreaseNumOfCoins();
            break;
        case Highlight::Level:
            settings.decreaseLevel();
            break;
        case Highlight::Mode:
            settings.switchMode();
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
            settings.increaseNumOfCoins();
            break;
        case Highlight::Level:
            settings.increaseLevel();
            break;
        case Highlight::Mode:
            settings.switchMode();
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
    view.displaySettings(settings);
}




