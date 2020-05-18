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

//************************** Constructor
GameSettingsScreen::GameSettingsScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const GameSettingsScreen::Highlight GameSettingsScreen::currHighlight() const {
    return highlight;
}



//************************** Arrow button handling
void GameSettingsScreen::highlightUp(Controller &controller) {
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

void GameSettingsScreen::highlightDown(Controller &controller) {
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

void GameSettingsScreen::highlightLeft(Controller &controller) {
    switch (highlight) {
        case Highlight::NumOfCoins:
            controller.decreaseNumOfCoins();
            break;
        case Highlight::Level:
            controller.decreaseLevel();
            break;
        case Highlight::Mode:
            controller.switchMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}

void GameSettingsScreen::highlightRight(Controller &controller) {
    switch (highlight) {
        case Highlight::NumOfCoins:
            controller.increaseNumOfCoins();
            break;
        case Highlight::Level:
            controller.increaseLevel();
            break;
        case Highlight::Mode:
            controller.switchMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}



//************************** Character input handling
void GameSettingsScreen::onCharInput(Controller &controller, const char inputChar) {}



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
void GameSettingsScreen::triggerDisplay(Controller &controller, View &interface) {
    interface.displayScreen(*this);
    controller.displaySettings();
    
}




