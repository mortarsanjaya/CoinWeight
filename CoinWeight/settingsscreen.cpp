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
#include <vector>

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

    view.drawString(300, 50, "Coin Weight");
    
    const std::vector<std::string> options {
        "Number of Coins:", "Level:", "Mode:"
    };
    
    for (size_t i = 0; i < options.size(); ++i) {
        view.drawString(300, 300 + i * RenderUtil::total_string_height, options[i]);
    }
    
    const std::vector<std::string> screenSwitches {
        "Start Game", "Go Back"
    };
    
    for (size_t i = 0; i < screenSwitches.size(); ++i) {
        view.drawString(350, 400 + i * RenderUtil::total_string_height, screenSwitches[i]);
    }

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
    
    const std::string gameModeStr = []() -> std::string {
        switch (settings.mode) {
            case GameMode::Standard:
                return "Human";
                break;
            case GameMode::Computer:
                return "Computer";
                break;
        }
    }();
    
    view.drawString(400, 300, std::to_string(settings.nCoins));
    view.drawString(400, 300 + RenderUtil::total_string_height, gameLevelStr);
    view.drawString(400, 300 + 2 * RenderUtil::total_string_height, gameModeStr);
    
    switch (highlight) {
        case Highlight::NumOfCoins:
            RenderUtil::drawBoxOverString(view, 400, 300, std::to_string(settings.nCoins));
            break;
        case Highlight::Level:
            RenderUtil::drawBoxOverString(view, 400, 300 + RenderUtil::total_string_height, gameLevelStr);
            break;
        case Highlight::Mode:
            RenderUtil::drawBoxOverString(view, 400, 300 + 2 * RenderUtil::total_string_height, gameModeStr);
            break;
        case Highlight::Start:
            RenderUtil::drawBoxOverString(view, 350, 400, screenSwitches[0]);
            break;
        case Highlight::GoBack:
            RenderUtil::drawBoxOverString(view, 350, 400 + RenderUtil::total_string_height, screenSwitches[1]);
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
