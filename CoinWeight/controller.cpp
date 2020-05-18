//
//  controller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#include "controller.hpp"
#include "screenfactory.hpp"

//************************** Constructor
Controller::Controller(std::unique_ptr<View> ui) :
ui(std::move(ui)), screen() {
    switchToTitle();
}



//************************** Screen switching
void Controller::switchToTitle() {
    screen = ScreenFactory::createTitleScreen();
}

void Controller::switchToInstruction() {
    screen = ScreenFactory::createInstructionScreen();
}

void Controller::switchToCredit() {
    screen = ScreenFactory::createCreditScreen();
}

void Controller::switchToGameSettings() {
    screen = ScreenFactory::createGameSettingsScreen();
}

void Controller::switchToGamePlay() {
    // ...
}

void Controller::switchToGameOver(const bool isWin) {
    screen = ScreenFactory::createGameOverScreen(isWin);
}



//************************** Game-related operations
void Controller::changeCoinGroup(const size_t coinIndex, const CoinGroup newGroup) {
    // ...
}

void Controller::compareWeight() {
    // ...
}

void Controller::guessFakeCoins() {
    // ...
}

void Controller::sendMove() {
    // ...
}



//************************** Input processing
void Controller::processInput() {
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
void Controller::updateDisplay() {
    screen->triggerDisplay(*this, *ui);
}
