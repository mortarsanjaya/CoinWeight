//
//  instructionscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "instructionscreen.hpp"
#include "view.hpp"
#include "controller.hpp"

//************************** Constructor
InstructionScreen::InstructionScreen() {}



//************************** Arrow button handling
void InstructionScreen::highlightUp() {}

void InstructionScreen::highlightDown() {}

void InstructionScreen::highlightLeft() {}

void InstructionScreen::highlightRight() {}



//************************** Character input handling
void InstructionScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void InstructionScreen::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void InstructionScreen::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
