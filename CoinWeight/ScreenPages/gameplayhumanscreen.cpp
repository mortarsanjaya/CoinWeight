//
//  gameplayhumanscreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplayhumanscreen.hpp"
#include "gameview.hpp"
#include "gameui.hpp"

//************************** Constructor
GamePlayHumanScreen::GamePlayHumanScreen(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow) :
buttonHighlight(ButtonHighlight::Weigh),
coinNavigator(nCoinsTotal, nRowsDisplay, nCoinsPerRow),
isOnButtonHighlight(false)
{}



//************************** Field accessors
const GamePlayHumanScreen::ButtonHighlight
GamePlayHumanScreen::currButtonHighlight() const {
    return buttonHighlight;
}

const size_t GamePlayHumanScreen::coinDisplayTopRowIndex() const {
    return coinNavigator.currTopRow();
}

const size_t GamePlayHumanScreen::coinHighlightIndex() const {
    return coinNavigator.currIndex();
}

const size_t GamePlayHumanScreen::coinHighlightRow() const {
    return coinNavigator.currRow();
}

const size_t GamePlayHumanScreen::coinHighlightColumn() const {
    return coinNavigator.currColumn();
}

const bool GamePlayHumanScreen::onButtonHighlight() const {
    return isOnButtonHighlight;
}



//************************** Arrow button handling
//**** Main
void GamePlayHumanScreen::highlightUp(GameView &view) {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayHumanScreen::highlightDown(GameView &view) {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayHumanScreen::highlightLeft(GameView &view) {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayHumanScreen::highlightRight(GameView &view) {
    if (isOnButtonHighlight) {
        buttonHighlightRight();
    } else {
        coinHighlightRight();
    }
}

//**** Helper (button highlight)
void GamePlayHumanScreen::buttonHighlightUp() {
    switch (buttonHighlight) {
        case ButtonHighlight::Weigh:
            break;
        case ButtonHighlight::Guess:
            buttonHighlight = ButtonHighlight::Weigh;
            break;
    }
}

void GamePlayHumanScreen::buttonHighlightDown() {
    switch (buttonHighlight) {
        case ButtonHighlight::Weigh:
            buttonHighlight = ButtonHighlight::Guess;
            break;
        case ButtonHighlight::Guess:
            break;
    }
}

void GamePlayHumanScreen::buttonHighlightLeft() {}

void GamePlayHumanScreen::buttonHighlightRight() {
    transitionToCoinHighlight();
}


//**** Helper (coin highlight)
void GamePlayHumanScreen::coinHighlightUp() {
    coinNavigator.scrollUp();
}

void GamePlayHumanScreen::coinHighlightDown() {
    coinNavigator.scrollDown();
}

void GamePlayHumanScreen::coinHighlightLeft() {
    if (coinNavigator.currRow() == 0) {
        transitionToButtonHighlight();
    } else {
        coinNavigator.scrollLeft();
    }
}

void GamePlayHumanScreen::coinHighlightRight() {
    coinNavigator.scrollRight();
}

//**** Helper (transition)
void GamePlayHumanScreen::transitionToButtonHighlight() {
    isOnButtonHighlight = true;
}

void GamePlayHumanScreen::transitionToCoinHighlight() {
    isOnButtonHighlight = false;
}



//************************** Character input handling
void GamePlayHumanScreen::onCharInput(GameView &view, const char inputChar) {
    if (!isOnButtonHighlight) {
        switch (inputChar) {
            case '0':
                view.changeCoinGroup(coinHighlightIndex(), CoinGroup::NoSelect);
                break;
            case '1':
                view.changeCoinGroup(coinHighlightIndex(), CoinGroup::LeftWeigh);
                break;
            case '2':
                view.changeCoinGroup(coinHighlightIndex(), CoinGroup::RightWeigh);
                break;
            case '3':
                view.changeCoinGroup(coinHighlightIndex(), CoinGroup::Guess);
                break;
            default:
                break;
        }
    }
}



//************************** Return button handling
void GamePlayHumanScreen::onReturnButton(GameView &view) {
    if (isOnButtonHighlight) {
        switch (buttonHighlight) {
            case ButtonHighlight::Weigh:
                view.compareWeight();
                break;
            case ButtonHighlight::Guess:
                view.guessFakeCoins();
                break;
        }
    }
}



//************************** UI display
void GamePlayHumanScreen::triggerDisplay(GameView &view, GameUI &interface) {
    interface.displayScreen(*this);
}
