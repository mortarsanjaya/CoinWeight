//
//  instruction.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "instruction.hpp"
#include "model.hpp"
#include "view.hpp"

using namespace CoinWeight;

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
void Instruction::onReturnButton(Model &model) {
    model.switchToTitle();
}



//************************** UI display
void Instruction::triggerDisplay(View &view) {
    view.displayLayoutInstruction();
}
