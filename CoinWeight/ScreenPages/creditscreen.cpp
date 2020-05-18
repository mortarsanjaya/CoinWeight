//
//  creditscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "creditscreen.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Constructor
CreditScreen::CreditScreen() {}



//************************** Arrow button handling
void CreditScreen::highlightUp() {}

void CreditScreen::highlightDown() {}

void CreditScreen::highlightLeft() {}

void CreditScreen::highlightRight() {}



//************************** Character input handling
void CreditScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void CreditScreen::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void CreditScreen::triggerDisplay(View &view) {
    view.displayScreen(*this);
}
