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
    displayLayout(view);
}

void Credit::displayLayout(ViewX11 &view) {
    view.clearWindow();
    view.setForeground(view.defaultFGColor);
    
    view.drawString(300, 300, "---");
    
    const std::string &returnStr = "Return";
    view.drawString(300 + view.border, 500 + view.total_string_height - view.border, returnStr);
    view.drawRectangle(300, 500, view.total_string_width(returnStr.size()), view.total_string_height);
    
    view.flushDisplay();
}
