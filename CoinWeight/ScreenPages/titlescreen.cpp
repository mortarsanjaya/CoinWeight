//
//  titlescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "titlescreen.hpp"
#include "gameui.hpp"
#include "gamecontroller.hpp"

//************************** Constructor
TitleScreen::TitleScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const TitleScreen::Highlight TitleScreen::currHighlight() const {
    return highlight;
}



//************************** Arrow button handling
void TitleScreen::highlightUp(GameController &controller) {
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

void TitleScreen::highlightDown(GameController &controller) {
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

void TitleScreen::highlightLeft(GameController &controller) {}

void TitleScreen::highlightRight(GameController &controller) {}



//************************** Character input handling
void TitleScreen::onCharInput(GameController &controller, const char inputChar) {}



//************************** Return button handling
void TitleScreen::onReturnButton(GameController &controller) {
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
void TitleScreen::triggerDisplay(GameController &controller, GameUI &interface) {
    interface.displayScreen(*this);
}
