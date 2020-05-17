//
//  titlescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "titlescreen.hpp"
#include "gameui.hpp"
#include "gameview.hpp"

//************************** Constructor
TitleScreen::TitleScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const TitleScreen::Highlight TitleScreen::currHighlight() const {
    return highlight;
}



//************************** Arrow button handling
void TitleScreen::highlightUp(GameView &view) {
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

void TitleScreen::highlightDown(GameView &view) {
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

void TitleScreen::highlightLeft(GameView &view) {}

void TitleScreen::highlightRight(GameView &view) {}



//************************** Character input handling
void TitleScreen::onCharInput(GameView &view, const char inputChar) {}



//************************** Return button handling
void TitleScreen::onReturnButton(GameView &view) {
    switch (highlight) {
        case Highlight::Play:
            view.switchToGameSettings();
            break;
        case Highlight::Instruction:
            view.switchToInstruction();
            break;
        case Highlight::Credit:
            view.switchToCredit();
            break;
    }
}



//************************** UI display
void TitleScreen::triggerDisplay(GameView &view, GameUI &interface) {
    interface.displayScreen(*this);
}
