//
//  gameover.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameover.hpp"
#include "model.hpp"
#include "viewx11.hpp"
#include "x11renderutil.hpp"

using namespace CoinWeight::X11;

//************************** Constructor
GameOver::GameOver(const bool doesPlayerWin) :
playerWin(doesPlayerWin) {}



//************************** Arrow button handling
void GameOver::onArrowUp() {}

void GameOver::onArrowDown() {}

void GameOver::onArrowLeft() {}

void GameOver::onArrowRight() {}



//************************** Character input handling
void GameOver::onCharInput(const char inputChar) {}



//************************** Return button handling
void GameOver::onReturnButton(Model &model) {
    model.switchToTitle();
}



//************************** UI display
void GameOver::triggerDisplay(Renderer &view) const {
    view.clearWindow();
    view.setForeground(Color::Default);
    
    if (playerWin) {
        view.drawString(300, 200, "You Win!");
    } else {
        view.drawString(300, 200, "You Lose!");
    }
    
    const std::string &returnStr = "Return";
    
    view.drawString(300 + RenderUtil::border, 500 + RenderUtil::total_string_height - RenderUtil::border, returnStr);
    view.drawRectangle(300, 500, RenderUtil::total_string_width(returnStr.size()), RenderUtil::total_string_height);
    
    view.flushDisplay();
}
