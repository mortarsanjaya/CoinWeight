//
//  creditscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "creditscreen.hpp"
#include "gameui.hpp"
#include "gameview.hpp"

//************************** Constructor
CreditScreen::CreditScreen() {}



//************************** Arrow button handling
void CreditScreen::highlightUp(GameView &view) {}

void CreditScreen::highlightDown(GameView &view) {}

void CreditScreen::highlightLeft(GameView &view) {}

void CreditScreen::highlightRight(GameView &view) {}



//************************** Character input handling
void CreditScreen::onCharInput(GameView &view, const char inputChar) {}



//************************** Return button handling
void CreditScreen::onReturnButton(GameView &view) {
    view.switchToTitle();
}



//************************** UI display
void CreditScreen::triggerDisplay(GameUI &interface) {
    interface.displayScreen(*this);
}
