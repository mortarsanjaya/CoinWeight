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
void CreditScreen::highlightUp(Controller &controller) {}

void CreditScreen::highlightDown(Controller &controller) {}

void CreditScreen::highlightLeft(Controller &controller) {}

void CreditScreen::highlightRight(Controller &controller) {}



//************************** Character input handling
void CreditScreen::onCharInput(Controller &controller, const char inputChar) {}



//************************** Return button handling
void CreditScreen::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void CreditScreen::triggerDisplay(Controller &controller, View &interface) {
    interface.displayScreen(*this);
}
