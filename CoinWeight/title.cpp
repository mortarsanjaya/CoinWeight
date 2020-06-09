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

using namespace CoinWeight;

//************************** Constructor
Title::Title() : highlight(defaultHighlight) {}



//************************** Arrow button handling
void Title::onArrowUp() {
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

void Title::onArrowDown() {
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

void Title::onArrowLeft() {}

void Title::onArrowRight() {}



//************************** Character input handling
void Title::onCharInput(const char inputChar) {}



//************************** Return button handling
void Title::onReturnButton(Model &model) {
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
void Title::triggerDisplay(ViewX11 &view) const {
    displayLayout(view);
    displayHighlight(view);
}

void Title::displayLayout(ViewX11 &view) const {
    view.clearWindow();
    view.setForeground(view.defaultFGColor);
    
    constexpr int text_x_pos = 300;
    constexpr int top_button_y_pos = 300;
    
    const std::string &playStr = "Play";
    const std::string &instrStr = "Instruction";
    const std::string &creditStr = "Credit";
    
    view.drawString(text_x_pos + view.border, 50, "Coin Weight");
    view.drawString(text_x_pos + view.border, top_button_y_pos +
        1 * view.total_string_height - view.border, playStr);
    view.drawString(text_x_pos + view.border, top_button_y_pos +
        2 * view.total_string_height - view.border, instrStr);
    view.drawString(text_x_pos + view.border, top_button_y_pos +
        3 * view.total_string_height - view.border, creditStr);
    
    view.flushDisplay();
}

void Title::displayHighlight(ViewX11 &view) const {
    
    constexpr int text_x_pos = 300;
    constexpr int top_button_y_pos = 300;
    
    switch (highlight) {
        case Title::Highlight::Play:
            view.drawRectangle(text_x_pos, top_button_y_pos, 34, view.total_string_height);
            break;
        case Title::Highlight::Instruction:
            view.drawRectangle(text_x_pos, top_button_y_pos + view.total_string_height, 76, view.total_string_height);
            break;
        case Title::Highlight::Credit:
            view.drawRectangle(text_x_pos, top_button_y_pos + 2 * view.total_string_height, 46, view.total_string_height);
            break;
    }
    
    view.flushDisplay();
}
