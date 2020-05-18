//
//  instructionscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "instructionscreen.hpp"
#include "gameui.hpp"
#include "gamecontroller.hpp"

//************************** Constructor
InstructionScreen::InstructionScreen() {}



//************************** Arrow button handling
void InstructionScreen::highlightUp(GameController &controller) {}

void InstructionScreen::highlightDown(GameController &controller) {}

void InstructionScreen::highlightLeft(GameController &controller) {}

void InstructionScreen::highlightRight(GameController &controller) {}



//************************** Character input handling
void InstructionScreen::onCharInput(GameController &controller, const char inputChar) {}



//************************** Return button handling
void InstructionScreen::onReturnButton(GameController &controller) {
    controller.switchToTitle();
}



//************************** UI display
void InstructionScreen::triggerDisplay(GameController &controller, GameUI &interface) {
    interface.displayScreen(*this);
}
