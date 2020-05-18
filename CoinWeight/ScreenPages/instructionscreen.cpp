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
void InstructionScreen::highlightUp(Controller &controller) {}

void InstructionScreen::highlightDown(Controller &controller) {}

void InstructionScreen::highlightLeft(Controller &controller) {}

void InstructionScreen::highlightRight(Controller &controller) {}



//************************** Character input handling
void InstructionScreen::onCharInput(Controller &controller, const char inputChar) {}



//************************** Return button handling
void InstructionScreen::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void InstructionScreen::triggerDisplay(Controller &controller, View &interface) {
    interface.displayScreen(*this);
}
