//
//  title.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "title.hpp"
#include "model.hpp"
#include "viewx11.hpp"
#include "x11renderutil.hpp"

#include <vector>
#include <string>

using namespace CoinWeight::X11;

//************************** Constructor
TitleScreen::TitleScreen() : highlight(defaultHighlight) {}



//************************** Arrow button handling
void TitleScreen::onArrowUp() {
    switch (highlight) {
        case Highlight::Play:
            highlight = Highlight::Play;
            break;
        case Highlight::Instruction:
            highlight = Highlight::Play;
            break;
        case Highlight::Credit:
            highlight = Highlight::Instruction;
            break;
    }
}

void TitleScreen::onArrowDown() {
    switch (highlight) {
        case Highlight::Play:
            highlight = Highlight::Instruction;
            break;
        case Highlight::Instruction:
            highlight = Highlight::Credit;
            break;
        case Highlight::Credit:
            highlight = Highlight::Credit;
            break;
    }
}

void TitleScreen::onArrowLeft() {}

void TitleScreen::onArrowRight() {}



//************************** Character input handling
void TitleScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void TitleScreen::onReturnButton(Model &model) {
    switch (highlight) {
        case Highlight::Play:
            model.switchToGameSettings();
            break;
        case Highlight::Instruction:
            model.switchToInstruction();
            break;
        case Highlight::Credit:
            model.switchToCredit();
            break;
    }
}



//************************** UI display
static constexpr int screen_name_x_pos = 300;
static constexpr int screen_name_y_pos = 50;
static const std::string screenName = "Coin Weight";
    
static constexpr int button_x_pos = 300;
static constexpr int button_y_pos_top = 300;
static const std::vector<std::string> buttons {
    "Play", "Instruction", "Credit"
};

void TitleScreen::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(Color::Default);
    
    view.drawString(button_x_pos + RenderUtil::border, screen_name_y_pos, screenName);
    for (size_t i = 0; i < buttons.size(); ++i) {
        view.drawString(button_x_pos + RenderUtil::border, button_y_pos_top +
            (i + 1) * RenderUtil::total_string_height - RenderUtil::border, buttons[i]);
    }
    
    view.drawRectangle(button_x_pos, button_y_pos_top + highlight * RenderUtil::total_string_height, RenderUtil::total_string_width(buttons[highlight].size()), RenderUtil::total_string_height);
    
    view.flushDisplay();
}
