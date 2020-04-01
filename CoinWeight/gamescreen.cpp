//
//  gamescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamescreen.hpp"

//***************************************************** Constructor
GameScreen::GameScreen(Page page, int highlight) :
    page(page), highlight(highlight) {}
    


//***************************************************** Field accessors
const GameScreen::Page GameScreen::currentScreen() const {
    return page;
}

const int GameScreen::currentHighlight() const {
    return highlight;
}



//***************************************************** Modifier functions
//**** Public
void GameScreen::incrementHighlight() {
    if (highlight < maxHighlight()) {
        ++highlight;
    }
}

void GameScreen::decrementHighlight() {
    if (highlight > minHighlight()) {
        --highlight;
    }
}

void GameScreen::transition(const Page nextScreen) {
    page = nextScreen;
    resetHighlight();
}


const int GameScreen::minHighlight() {
    return 0;
}

//**** Private
const int GameScreen::maxHighlight() {
    switch (page) {
        case Page::Main:
            return 2;
        case Page::Instruction:
            return 0;
        case Page::Credit:
            return 0;
        case Page::GameOption:
            return 2;
        case Page::GamePlayHuman:
            return 2;
        case Page::GamePlayComputer:
            return 0;
        case Page::GameOver:
            return 0;
    }
}

void GameScreen::resetHighlight() {
    highlight = 0;
}



//***************************************************** Game Screen Failure
GameScreenFailure::GameScreenFailure(std::string coreMessage) :
    Exception(coreMessage) {}

const std::string GameScreenFailure::headerMessage() const {
    return "Game Screen: ";
}
