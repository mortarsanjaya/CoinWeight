//
//  instructionscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "instructionscreen.hpp"
#include "gameui.hpp"
#include "gameview.hpp"

//************************** Constructor
InstructionScreen::InstructionScreen() {}



//************************** Arrow button handling
void InstructionScreen::highlightUp(GameView &view) {}

void InstructionScreen::highlightDown(GameView &view) {}

void InstructionScreen::highlightLeft(GameView &view) {}

void InstructionScreen::highlightRight(GameView &view) {}



//************************** Character input handling
void InstructionScreen::onCharInput(GameView &view, const char inputChar) {}



//************************** Return button handling
void InstructionScreen::onReturnButton(GameView &view) {
    view.switchToTitle();
}



//************************** UI display
void InstructionScreen::triggerDisplay(GameUI &interface) {
    interface.displayScreen(*this);
}
