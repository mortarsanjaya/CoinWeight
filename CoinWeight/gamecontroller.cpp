//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"
#include "screenfactory.hpp"

//************************** Constructor
GameController::GameController(std::unique_ptr<GameUI> ui) :
ui(std::move(ui)), screen() {
    switchToTitle();
}



//************************** Screen switching
void GameController::switchToTitle() {
    screen = ScreenFactory::createTitleScreen();
}

void GameController::switchToInstruction() {
    screen = ScreenFactory::createInstructionScreen();
}

void GameController::switchToCredit() {
    screen = ScreenFactory::createCreditScreen();
}

void GameController::switchToGameSettings() {
    screen = ScreenFactory::createGameSettingsScreen();
}

void GameController::switchToGamePlay() {
    // ...
}

void GameController::switchToGameOver(const bool isWin) {
    screen = ScreenFactory::createGameOverScreen(isWin);
}



//************************** Settings manipulation
void GameController::decreaseNumOfCoins() {
    settings.decreaseGameSize();
}

void GameController::increaseNumOfCoins() {
    settings.increaseGameSize();
}

void GameController::decreaseLevel() {
    settings.decreaseDifficulty();
}

void GameController::increaseLevel() {
    settings.increaseDifficulty();
}

void GameController::switchMode() {
    settings.switchMode();
}



//************************** Game-related operations
void GameController::changeCoinGroup(const size_t coinIndex, const CoinGroup newGroup) {
    // ...
}

void GameController::compareWeight() {
    // ...
}

void GameController::guessFakeCoins() {
    // ...
}

void GameController::sendMove() {
    // ...
}



//************************** Input processing
void GameController::processInput() {
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
void GameController::updateDisplay() {
    screen->triggerDisplay(*this, *ui);
}



//************************** Elements display
void GameController::displaySettings() {
    ui->displaySettings(settings);
}
