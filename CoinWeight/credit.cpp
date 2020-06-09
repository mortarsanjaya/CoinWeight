//
//  credit.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "credit.hpp"
#include "model.hpp"
#include "viewx11.hpp"

using namespace CoinWeight;

//************************** Constructor
Credit::Credit() {}



//************************** Arrow button handling
void Credit::onArrowUp() {}

void Credit::onArrowDown() {}

void Credit::onArrowLeft() {}

void Credit::onArrowRight() {}



//************************** Character input handling
void Credit::onCharInput(const char inputChar) {}



//************************** Return button handling
void Credit::onReturnButton(Model &model) {
    model.switchToTitle();
}



//************************** UI display
void Credit::triggerDisplay(ViewX11 &view) {
    view.displayLayoutCredit();
}
