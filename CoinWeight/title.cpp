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
void TitleScreen::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(view.defaultFGColor);
    
    constexpr int text_x_pos = 300;
    constexpr int top_button_y_pos = 300;
    
    const std::string screenName = "Coin Weight";
    const std::vector<std::string> buttons {
        "Play", "Instruction", "Credit"
    };
    
    view.drawString(text_x_pos + view.border, 50, screenName);
    for (size_t i = 0; i < buttons.size(); ++i) {
        view.drawString(text_x_pos + view.border, top_button_y_pos +
            (i + 1) * view.total_string_height - view.border, buttons[i]);
    }
    
    switch (highlight) {
        case TitleScreen::Highlight::Play:
            view.drawRectangle(text_x_pos, top_button_y_pos, 34, view.total_string_height);
            break;
        case TitleScreen::Highlight::Instruction:
            view.drawRectangle(text_x_pos, top_button_y_pos + view.total_string_height, 76, view.total_string_height);
            break;
        case TitleScreen::Highlight::Credit:
            view.drawRectangle(text_x_pos, top_button_y_pos + 2 * view.total_string_height, 46, view.total_string_height);
            break;
    }
    
    view.flushDisplay();
}
