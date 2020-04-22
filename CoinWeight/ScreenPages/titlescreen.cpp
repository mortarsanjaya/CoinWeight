//
//  titlescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "titlescreen.hpp"

//************************** Constructor
TitleScreen::TitleScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const TitleScreen::Highlight TitleScreen::currHighlight() const {
    return highlight;
}



//************************** Manual highlight switch
void TitleScreen::highlightSwitch(const Highlight highlight) {
    this->highlight = highlight;
}



//************************** Reset highlight
void TitleScreen::resetHighlight() {
    highlight = defaultHighlight;
}



//************************** Arrow button highlight switch
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
