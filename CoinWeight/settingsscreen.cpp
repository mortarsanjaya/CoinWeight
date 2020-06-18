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
#include "renderutil.hpp"

#include <vector>
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
static constexpr void drawScreenName(Renderer &view) {
    view.drawString(300, 50, "Coin Weight");
}

static constexpr int screen_name_x_pos = 300;
static constexpr int screen_name_y_pos = 50;
static const std::string screenName = "Coin Weight";

static constexpr int options_x_pos = 300;
static constexpr int options_y_pos_top = 300;
static const std::vector<std::string> options {
    "Number of Coins:", "Level:", "Mode:"
};

static constexpr int start_game_x_pos = 350;
static constexpr int start_game_y_pos = 400;
static const std::string startGame = "Start Game";

static constexpr int go_back_x_pos = start_game_x_pos;
static constexpr int go_back_y_pos = start_game_y_pos + RenderUtil::total_string_height;
static const std::string goBack = "Go Back";



void SettingsScreen::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(RenderUtil::defaultFGColor);
    
    view.drawString(screen_name_x_pos, screen_name_y_pos, screenName);
    for (int i = 0; i < 3; ++i) {
        view.drawString(options_x_pos, options_y_pos_top + (i + 1) * RenderUtil::total_string_height - RenderUtil::border, options[i]);
    }
    
    view.drawString(start_game_x_pos, start_game_y_pos, startGame);
    view.drawString(go_back_x_pos, go_back_y_pos, goBack);
    
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
    
    view.flushDisplay();
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
