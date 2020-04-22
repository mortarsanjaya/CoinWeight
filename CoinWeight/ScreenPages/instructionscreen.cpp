//
//  instructionscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "instructionscreen.hpp"

//************************** Constructor
InstructionScreen::InstructionScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const InstructionScreen::Highlight InstructionScreen::currHighlight() const {
    return highlight;
}



//************************** Manual highlight switch
void InstructionScreen::highlightSwitch(const Highlight highlight) {
    this->highlight = highlight;
}



//************************** Reset highlight
void InstructionScreen::resetHighlight() {
    highlight = defaultHighlight;
}



//************************** Arrow button highlight switch
void InstructionScreen::highlightUp() {
    switch (highlight) {
        case Highlight::Return:
            highlight = Highlight::Return;
            break;
    }
}

void InstructionScreen::highlightDown() {
    switch (highlight) {
        case Highlight::Return:
            highlight = Highlight::Return;
            break;
    }
}

void InstructionScreen::highlightLeft() {}
void InstructionScreen::highlightRight() {}
