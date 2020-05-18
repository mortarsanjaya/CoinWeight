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
Instruction::Instruction() {}



//************************** Arrow button handling
void Instruction::highlightUp() {}

void Instruction::highlightDown() {}

void Instruction::highlightLeft() {}

void Instruction::highlightRight() {}



//************************** Character input handling
void Instruction::onCharInput(const char inputChar) {}



//************************** Return button handling
void Instruction::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void Instruction::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
