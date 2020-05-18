//
//  titlescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "titlescreen.hpp"
#include "view.hpp"
#include "controller.hpp"

//************************** Constructor
TitleScreen::TitleScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const TitleScreen::Highlight TitleScreen::currHighlight() const {
    return highlight;
}



//************************** Arrow button handling
void TitleScreen::highlightUp() {
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

void TitleScreen::highlightDown() {
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

void TitleScreen::highlightLeft() {}

void TitleScreen::highlightRight() {}



//************************** Character input handling
void TitleScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void TitleScreen::onReturnButton(Controller &controller) {
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
void TitleScreen::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
