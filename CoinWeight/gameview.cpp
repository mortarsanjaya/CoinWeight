//
//  gameview.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameview.hpp"
#include "screenfactory.hpp"

//************************** Constructor
GameView::GameView(std::unique_ptr<GameUI> ui) :
ui(std::move(ui)), screen() {
    switchToTitle();
}



//************************** Screen switching
void GameView::switchToTitle() {
    screen = ScreenFactory::createTitleScreen();
}

void GameView::switchToInstruction() {
    screen = ScreenFactory::createInstructionScreen();
}

void GameView::switchToCredit() {
    screen = ScreenFactory::createCreditScreen();
}

void GameView::switchToGameSettings() {
    screen = ScreenFactory::createGameSettingsScreen();
}

void GameView::switchToGamePlay() {
    // ...
}

void GameView::switchToGameOver(const bool isWin) {
    screen = ScreenFactory::createGameOverScreen(isWin);
}



//************************** Settings manipulation
void GameView::decreaseNumOfCoins() {
    settings.decreaseGameSize();
}

void GameView::increaseNumOfCoins() {
    settings.increaseGameSize();
}

void GameView::decreaseLevel() {
    settings.decreaseDifficulty();
}

void GameView::increaseLevel() {
    settings.increaseDifficulty();
}

void GameView::switchMode() {
    settings.switchMode();
}



//************************** Game-related operations
void GameView::changeCoinGroup(const size_t coinIndex, const CoinGroup newGroup) {
    // ...
}

void GameView::compareWeight() {
    // ...
}

void GameView::guessFakeCoins() {
    // ...
}

void GameView::sendMove() {
    // ...
}



//************************** Input processing
void GameView::processInput() {
    const Input input = ui->nextInput();
    switch (input.inputType()) {
        case Input::Type::Unknown:
            break;
        case Input::Type::Char:
            screen->onCharInput(*this, input.whatChar());
            break;
        case Input::Type::Arrow:
            switch (input.whatArrow()) {
                case Input::Arrow::Up:
                    screen->highlightUp(*this);
                    break;
                case Input::Arrow::Down:
                    screen->highlightDown(*this);
                    break;
                case Input::Arrow::Left:
                    screen->highlightLeft(*this);
                    break;
                case Input::Arrow::Right:
                    screen->highlightRight(*this);
                    break;
            }
            break;
        case Input::Type::Return:
            screen->onReturnButton(*this);
            break;
    }
}



//************************** Display updating
void GameView::updateDisplay() {
    screen->triggerDisplay(*ui);
}
