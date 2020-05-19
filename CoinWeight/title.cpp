//
//  title.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "title.hpp"
#include "view.hpp"
#include "controller.hpp"

//************************** Constructor
Title::Title() : highlight(defaultHighlight) {}



//************************** Field accessors
const Title::Highlight Title::currHighlight() const {
    return highlight;
}



//************************** Arrow button handling
void Title::highlightUp() {
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

void Title::highlightDown() {
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

void Title::highlightLeft() {}

void Title::highlightRight() {}



//************************** Character input handling
void Title::onCharInput(const char inputChar) {}



//************************** Return button handling
void Title::onReturnButton(Controller &controller) {
    switch (highlight) {
        case Highlight::Play:
            controller.switchToGameSettings();
            break;
        case Highlight::Instruction:
            controller.switchToInstruction();
            break;
        case Highlight::Credit:
            controller.switchToCredit();
            break;
    }
}



//************************** UI display
void Title::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
