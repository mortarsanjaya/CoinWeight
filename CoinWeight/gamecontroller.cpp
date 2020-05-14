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



//************************** Input function
//**** Arrow, Main
void GameController::onScreenArrowInputUp(GameModel *model) {
    model->mainScreenOnUpButton();
}

void GameController::onScreenArrowInputDown(GameModel *model) {
    model->mainScreenOnDownButton();
}

void GameController::onScreenArrowInputLeft(GameModel *model) {
    model->mainScreenOnLeftButton();
}

void GameController::onScreenArrowInputRight(GameModel *model) {
    model->mainScreenOnRightButton();
}

void GameController::onScreenArrowInput(GameModel *model, const Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onScreenArrowInputUp(model);
            break;
        case Input::Arrow::Down:
            onScreenArrowInputDown(model);
            break;
        case Input::Arrow::Left:
            onScreenArrowInputLeft(model);
            break;
        case Input::Arrow::Right:
            onScreenArrowInputRight(model);
            break;
    }
}



//**** Char
void GameController::onCharInput0(GameModel *model) {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->deselectCoin();
    }
}

void GameController::onCharInput1(GameModel *model) {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToLeftGroup();
    }
}

void GameController::onCharInput2(GameModel *model) {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToRightGroup();
    }
}

void GameController::onCharInput3(GameModel *model) {
    if (model->currScreen() == GameScreen::Page::GamePlayHuman) {
        model->selectCoinToGuess();
    }
}

void GameController::onReturnButton(GameModel *model) {
    model->mainScreenOnReturnButton();
}

void GameController::onCharInput(GameModel *model, const char charInp) {
    switch (charInp) {
        case '0':
            onCharInput0(model);
            break;
        case '1':
            onCharInput1(model);
            break;
        case '2':
            onCharInput2(model);
            break;
        case '3':
            onCharInput3(model);
            break;
        case '\n':
            onReturnButton(model);
        default:
            break;
    }
}



//************************** Input process function
void GameController::onReceivingInput(GameModel *model, const Input &inp) {
    switch (inp.inputType()) {
        case Input::Type::Unknown:
            break;
        case Input::Type::Char:
            onCharInput(model, inp.whatChar());
            break;
        case Input::Type::Arrow:
            onScreenArrowInput(model, inp.whatArrow());
            break;
    }
}
