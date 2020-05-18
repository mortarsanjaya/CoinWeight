//
//  creditscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "creditscreen.hpp"
#include "gameui.hpp"
#include "gamecontroller.hpp"

//************************** Constructor
CreditScreen::CreditScreen() {}



//************************** Arrow button handling
void CreditScreen::highlightUp(GameController &controller) {}

void CreditScreen::highlightDown(GameController &controller) {}

void CreditScreen::highlightLeft(GameController &controller) {}

void CreditScreen::highlightRight(GameController &controller) {}



//************************** Character input handling
void CreditScreen::onCharInput(GameController &controller, const char inputChar) {}



//************************** Return button handling
void CreditScreen::onReturnButton(GameController &controller) {
    controller.switchToTitle();
}



//************************** UI display
void CreditScreen::triggerDisplay(GameController &controller, GameUI &interface) {
    interface.displayScreen(*this);
}
