//
//  gamesettingsscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesettingsscreen.hpp"
#include "gameview.hpp"
#include "gameui.hpp"

//************************** Constructor
GameSettingsScreen::GameSettingsScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const GameSettingsScreen::Highlight GameSettingsScreen::currHighlight() const {
    return highlight;
}



//************************** Arrow button handling
void GameSettingsScreen::highlightUp(GameView &view) {
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

void GameSettingsScreen::highlightDown(GameView &view) {
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

void GameSettingsScreen::highlightLeft(GameView &view) {
    switch (highlight) {
        case Highlight::NumOfCoins:
            view.decreaseNumOfCoins();
            break;
        case Highlight::Level:
            view.decreaseLevel();
            break;
        case Highlight::Mode:
            view.switchMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}

void GameSettingsScreen::highlightRight(GameView &view) {
    switch (highlight) {
        case Highlight::NumOfCoins:
            view.increaseNumOfCoins();
            break;
        case Highlight::Level:
            view.increaseLevel();
            break;
        case Highlight::Mode:
            view.switchMode();
            break;
        case Highlight::StartGame:
            break;
        case Highlight::GoBack:
            break;
    }
}



//************************** Character input handling
void GameSettingsScreen::onCharInput(GameView &view, const char inputChar) {}



//************************** Return button handling
void GameSettingsScreen::onReturnButton(GameView &view) {
    switch (highlight) {
        case Highlight::StartGame:
            view.switchToGamePlay();
            break;
        case Highlight::GoBack:
            view.switchToTitle();
            break;
        default:
            break;
    }
}



//************************** UI display
void GameSettingsScreen::triggerDisplay(GameView &view, GameUI &interface) {
    interface.displayScreen(*this);
    view.displaySettings();
    
}




