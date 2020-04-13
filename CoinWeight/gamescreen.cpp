//
//  gamescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamescreen.hpp"
#include "exception.hpp"

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
//**** Private
const int GameScreen::minHighlight() {
    return 0;
}

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
            return 1;
    }
}

void GameScreen::resetHighlight() {
    highlight = 0;
}

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

void GameScreen::playerWins() {
    if (page != Page::GameOver) {
        throw ("Wrong page: Not Game Over");
    }
    highlight = 1;
}

void GameScreen::playerLoses() {
    if (page != Page::GameOver) {
        throw Exception<GameScreen>("Wrong page: Not Game Over");
    }
    highlight = 0;
}



//***************************************************** Game Screen Exception header message
template<> const std::string exceptionHeaderMessage<GameScreen>() {
    return "Game Screen: ";
}
