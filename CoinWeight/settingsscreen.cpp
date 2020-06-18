//
//  settingsscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-17.
//  Copyright © 2020 -. All rights reserved.
//

#include "settingsscreen.hpp"

#include "model.hpp"
#include "viewx11.hpp"
#include "x11renderutil.hpp"

#include <string>

using namespace CoinWeight;
using namespace CoinWeight::X11;

//************************** Static members
GameSettings SettingsScreen::settings {
    defaultNumOfCoins,
    defaultLevel,
    defaultMode
};



//************************** Constructor
SettingsScreen::SettingsScreen() : highlight(defaultHighlight) {}



//************************** Arrow button handling
void SettingsScreen::onArrowUp() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            break;
        case Highlight::Level:
            highlight = Highlight::NumOfCoins;
            break;
        case Highlight::Mode:
            highlight = Highlight::Level;
            break;
        case Highlight::Start:
            highlight = Highlight::Mode;
            break;
        case Highlight::GoBack:
            highlight = Highlight::Start;
            break;
    }
}

void SettingsScreen::onArrowDown() {
    switch (highlight) {
        case Highlight::NumOfCoins:
            highlight = Highlight::Level;
            break;
        case Highlight::Level:
            highlight = Highlight::Mode;
            break;
        case Highlight::Mode:
            highlight = Highlight::Start;
            break;
        case Highlight::Start:
            highlight = Highlight::GoBack;
            break;
        case Highlight::GoBack:
            break;
    }
}

void SettingsScreen::onArrowLeft() {
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
        case Highlight::Start:
            break;
        case Highlight::GoBack:
            break;
    }
}

void SettingsScreen::onArrowRight() {
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
        case Highlight::Start:
            break;
        case Highlight::GoBack:
            break;
    }
}



//************************** Character input handling
void SettingsScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void SettingsScreen::onReturnButton(Model &model) {
    switch (highlight) {
        case Highlight::Start:
            model.switchToGamePlay(settings.nCoins, settings.level, settings.mode);
            break;
        case Highlight::GoBack:
            model.switchToTitle();
            break;
        default:
            break;
    }
}



//************************** UI display
void SettingsScreen::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(Color::Default);
    
    displayLayout(view);
    displaySettingsValue(view);
    displayHighlight(view);
    
    view.flushDisplay();
}

void SettingsScreen::displayLayout(Renderer &view) const {
    view.drawString(300, 50, "Coin Weight");
    view.drawString(300, 300 + RenderUtil::total_string_height - RenderUtil::border, "Number of Coins:");
    view.drawString(300, 300 + 2 * RenderUtil::total_string_height - RenderUtil::border, "Level:");
    view.drawString(300, 300 + 3 * RenderUtil::total_string_height - RenderUtil::border, "Mode:");
    
    const std::string &startGameStr = "Start Game";
    const std::string &goBackStr = "Go Back";
    
    
    view.drawString(350 + RenderUtil::border, 400 + RenderUtil::total_string_height - RenderUtil::border, startGameStr);
    view.drawString(350 + RenderUtil::border, 400 + 2 * RenderUtil::total_string_height - RenderUtil::border, goBackStr);
}

void SettingsScreen::displaySettingsValue(Renderer &view) const {
    const std::string gameLevelStr = []() -> std::string {
        switch (settings.level) {
            case GameLevel::Easy:
                return "Easy";
            case GameLevel::Medium:
                return "Medium";
            case GameLevel::Hard:
                return "Hard";
            }
    }();
    
    view.drawString(400 + RenderUtil::border, 300 + RenderUtil::total_string_height - RenderUtil::border, std::to_string(settings.nCoins));
    view.drawString(400 + RenderUtil::border, 300 + 2 * RenderUtil::total_string_height - RenderUtil::border, gameLevelStr);
    switch (settings.mode) {
        case GameMode::Standard:
            view.drawString(400 + RenderUtil::border, 300 + 3 * RenderUtil::total_string_height - RenderUtil::border, "Human");
            break;
        case GameMode::Computer:
            view.drawString(400 + RenderUtil::border, 300 + 3 * RenderUtil::total_string_height - RenderUtil::border, "Computer");
            break;
    }
}

void SettingsScreen::displayHighlight(Renderer &view) const {
    switch (highlight) {
        case Highlight::NumOfCoins:
            view.drawRectangle(400, 300, 100, RenderUtil::total_string_height);
            break;
        case Highlight::Level:
            view.drawRectangle(400, 300 + RenderUtil::total_string_height, 100, RenderUtil::total_string_height);
            break;
        case Highlight::Mode:
            view.drawRectangle(400, 300 + 2 * RenderUtil::total_string_height, 100, RenderUtil::total_string_height);
            break;
        case Highlight::Start:
            view.drawRectangle(350, 400, 100, RenderUtil::total_string_height);
            break;
        case Highlight::GoBack:
            view.drawRectangle(350, 400 + RenderUtil::total_string_height, 100, RenderUtil::total_string_height);
            break;
    }
}



//************************** Member modifier functions
void SettingsScreen::increaseNumOfCoins() {
    if (settings.nCoins < numOfCoinsUpperBound) {
        ++settings.nCoins;
    }
}

void SettingsScreen::decreaseNumOfCoins() {
    if (settings.nCoins > numOfCoinsLowerBound) {
        --settings.nCoins;
    }
}

void SettingsScreen::increaseLevel() {
    switch (settings.level) {
        case GameLevel::Easy:
            settings.level = GameLevel::Medium;
            break;
        case GameLevel::Medium:
            settings.level = GameLevel::Hard;
            break;
        case GameLevel::Hard:
            settings.level = GameLevel::Hard;
            break;
    }
}

void SettingsScreen::decreaseLevel() {
    switch (settings.level) {
        case GameLevel::Easy:
            settings.level = GameLevel::Easy;
            break;
        case GameLevel::Medium:
            settings.level = GameLevel::Easy;
            break;
        case GameLevel::Hard:
            settings.level = GameLevel::Medium;
            break;
    }
}

void SettingsScreen::nextMode() {
    switch (settings.mode) {
        case GameMode::Standard:
            settings.mode = GameMode::Computer;
            break;
        case GameMode::Computer:
            settings.mode = GameMode::Standard;
            break;
    }
}

void SettingsScreen::prevMode() {
    switch (settings.mode) {
        case GameMode::Standard:
            settings.mode = GameMode::Computer;
            break;
        case GameMode::Computer:
            settings.mode = GameMode::Standard;
            break;
    }
}
