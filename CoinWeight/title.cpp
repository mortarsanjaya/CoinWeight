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
#include "renderutil.hpp"

#include <vector>
#include <string>

using namespace CoinWeight::X11;
using namespace RenderUtil;

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
    view.setForeground(RenderUtil::defaultFGColor);
    
    drawScreenName(view);
    drawOptionButtons(view);
    
    view.flushDisplay();
}

void TitleScreen::drawScreenName(Renderer &renderer) const {
    renderer.drawString(300, 50, "Coin Weight");
}

void TitleScreen::drawOptionButtons(Renderer &renderer) const {
    constexpr int x_pos = 300;
    constexpr int y_pos_top = 300;
    const std::vector<std::string> buttons {
        "Play", "Instruction", "Credit"
    };

    for (size_t i = 0; i < buttons.size(); ++i) {
        renderer.drawString(x_pos, y_pos_top + i * total_string_height, buttons[i]);
    }
    
    renderer.drawRectangle(x_pos - border, y_pos_top + (highlight - 1) * total_string_height + border, total_string_width(buttons[highlight].size()), total_string_height);
}
