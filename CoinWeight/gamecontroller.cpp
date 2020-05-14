//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"
#include "gamemodel.hpp"

//************************** Constructor
GameController::GameController() {}



//************************** Register model
void GameController::registerModel(const std::shared_ptr<GameModel> model) {
    this->model = model;
}



//************************** Input function
//**** Arrow, Main
void GameController::onScreenArrowInputUp() {
    model->mainScreenOnUpButton();
}

void GameController::onScreenArrowInputDown() {
    model->mainScreenOnDownButton();
}

void GameController::onScreenArrowInputLeft() {
    model->mainScreenOnLeftButton();
}

void GameController::onScreenArrowInputRight() {
    model->mainScreenOnRightButton();
}

void GameController::onScreenArrowInput(const Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onScreenArrowInputUp();
            break;
        case Input::Arrow::Down:
            onScreenArrowInputDown();
            break;
        case Input::Arrow::Left:
            onScreenArrowInputLeft();
            break;
        case Input::Arrow::Right:
            onScreenArrowInputRight();
            break;
    }
}



//**** Char
void GameController::onCharInput0() {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->deselectCoin();
    }
}

void GameController::onCharInput1() {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToLeftGroup();
    }
}

void GameController::onCharInput2() {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToRightGroup();
    }
}

void GameController::onCharInput3() {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->selectCoinToGuess();
    }
}

void GameController::onReturnButton() {
    model->mainScreenOnReturnButton();
}

void GameController::onCharInput(const char charInp) {
    switch (charInp) {
        case '0':
            onCharInput0();
            break;
        case '1':
            onCharInput1();
            break;
        case '2':
            onCharInput2();
            break;
        case '3':
            onCharInput3();
            break;
        case '\n':
            onReturnButton();
        default:
            break;
    }
}



//************************** Input process function
void GameController::onReceivingInput(const Input &inp) {
    switch (inp.inputType()) {
        case Input::Type::Unknown:
            break;
        case Input::Type::Char:
            onCharInput(inp.whatChar());
            break;
        case Input::Type::Arrow:
            onScreenArrowInput(inp.whatArrow());
            break;
    }
}
