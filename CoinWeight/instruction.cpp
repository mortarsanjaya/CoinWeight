//
//  instruction.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "instruction.hpp"
#include "model.hpp"
#include "viewx11.hpp"
#include "renderconst.hpp"

#include <vector>
#include <utility>

using namespace CoinWeight::X11;

//************************** Constructor
InstructionScreen::InstructionScreen() {}



//************************** Arrow button handling
void InstructionScreen::onArrowUp() {}

void InstructionScreen::onArrowDown() {}

void InstructionScreen::onArrowLeft() {}

void InstructionScreen::onArrowRight() {}



//************************** Character input handling
void InstructionScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void InstructionScreen::onReturnButton(Model &model) {
    model.switchToTitle();
}



//************************** UI display
static constexpr int x_pos_page_name = 300;
static constexpr int x_pos_page_instr = 320;
static constexpr int y_pos_initial = 100;
static constexpr int y_pos_increment = 20;

static const std::vector<std::pair<std::string, std::vector<std::string>>> displayStrings {
    {"Main Page:",
    {
        "Press Up/Down to select buttons.",
        "Press Enter/Return to switch page."
    }},
    
    {"Option Page:",
    {
        "Press Up/Down to select buttons."
        "Press Left/Right to change selected option.",
        "Press Enter/Return to start game."
    }},
    
    {"Game Play Page (Human play):",
    {
        "Press arrow keys to select buttons/select coins.",
        "Press '0' to move selected coin to the none (gold) set.",
        "Press '1' to move selected coin to the red (left) set.",
        "Press '2' to move selected coin to the blue (right) set.",
        "Press '3' to move selected coin to the green (guess) set."
    }},
    
    {"Game Play Page (Computer play):",
    {
        "Press arrow keys to select buttons/scroll coins."
        "Press Enter/Return at \"Next move\" to trigger the computer's move."
    }}
};

void InstructionScreen::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(RenderConst::defaultFGColor);
    
    int y_pos = y_pos_initial;
        
    for (auto pageStrList : displayStrings) {
        view.drawString(x_pos_page_name, y_pos, pageStrList.first);
        y_pos += y_pos_increment;
        for (int i = 0; i < pageStrList.second.size(); ++i) {
            view.drawString(x_pos_page_instr, y_pos, pageStrList.second[i]);
            y_pos += y_pos_increment;
        }
    }
    
    const std::string &returnStr = "Return";
    view.drawString(300 + RenderConst::border, 550 + RenderConst::total_string_height - RenderConst::border, returnStr);
    view.drawRectangle(300, 550, RenderConst::total_string_width(returnStr.size()), RenderConst::total_string_height);
    
    view.flushDisplay();
}
