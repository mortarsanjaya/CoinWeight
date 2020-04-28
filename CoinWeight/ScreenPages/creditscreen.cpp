//
//  creditscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "creditscreen.hpp"

//************************** Constructor
CreditScreen::CreditScreen() : highlight(defaultHighlight) {}



//************************** Field accessors
const CreditScreen::Highlight CreditScreen::currHighlight() const {
    return highlight;
}



//************************** Manual highlight switch
void CreditScreen::highlightSwitch(const Highlight highlight) {
    this->highlight = highlight;
}



//************************** Reset highlight
void CreditScreen::resetHighlight() {
    highlight = defaultHighlight;
}


//************************** Arrow button highlight switch
void CreditScreen::highlightUp() {}
void CreditScreen::highlightDown() {}
void CreditScreen::highlightLeft() {}
void CreditScreen::highlightRight() {}
