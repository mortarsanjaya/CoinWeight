//
//  credit.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "credit.hpp"
#include "controller.hpp"
#include "view.hpp"

//************************** Constructor
Credit::Credit() {}



//************************** Arrow button handling
void Credit::highlightUp() {}

void Credit::highlightDown() {}

void Credit::highlightLeft() {}

void Credit::highlightRight() {}



//************************** Character input handling
void Credit::onCharInput(const char inputChar) {}



//************************** Return button handling
void Credit::onReturnButton(Controller &controller) {
    controller.switchToTitle();
}



//************************** UI display
void Credit::triggerDisplay(View &view) {
    view.displayLayoutCredit();
}
