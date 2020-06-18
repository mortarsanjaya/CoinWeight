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
#include "renderconst.hpp"

using namespace CoinWeight::X11;

//************************** Constructor
CreditScreen::CreditScreen() {}



//************************** Arrow button handling
void CreditScreen::onArrowUp() {}

void CreditScreen::onArrowDown() {}

void CreditScreen::onArrowLeft() {}

void CreditScreen::onArrowRight() {}



//************************** Character input handling
void CreditScreen::onCharInput(const char inputChar) {}



//************************** Return button handling
void CreditScreen::onReturnButton(Model &model) {
    model.switchToTitle();
}



//************************** UI display
void CreditScreen::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(RenderConst::defaultFGColor);
    
    view.drawString(300, 300, "---");
    
    const std::string &returnStr = "Return";
    view.drawString(300 + RenderConst::border, 500 + RenderConst::total_string_height - RenderConst::border, returnStr);
    view.drawRectangle(300, 500, RenderConst::total_string_width(returnStr.size()), RenderConst::total_string_height);
    
    view.flushDisplay();
}
