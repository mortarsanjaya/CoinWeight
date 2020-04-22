//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"

//***************************************************** Constructor
GameController::GameController() {}



//***************************************************** Input function
//**** Arrow, Main
void GameController::onMainScreenArrowInputUp(GameModel &model) {
    model.mainScreenOnUpButton();
}

void GameController::onMainScreenArrowInputDown(GameModel &model) {
    model.mainScreenOnDownButton();
}

void GameController::onMainScreenArrowInputLeft(GameModel &model) {
    model.mainScreenOnLeftButton();
}

void GameController::onMainScreenArrowInputRight(GameModel &model) {
    model.mainScreenOnRightButton();
}

void GameController::onMainScreenArrowInput(GameModel &model, const Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onMainScreenArrowInputUp(model);
            break;
        case Input::Arrow::Down:
            onMainScreenArrowInputDown(model);
            break;
        case Input::Arrow::Left:
            onMainScreenArrowInputLeft(model);
            break;
        case Input::Arrow::Right:
            onMainScreenArrowInputRight(model);
            break;
    }
}

//**** Arrow, History
void GameController::onHistoryScreenArrowInputUp(GameModel &model) {}
void GameController::onHistoryScreenArrowInputDown(GameModel &model) {}

void GameController::onHistoryScreenArrowInputLeft(GameModel &model) {
    model.historyScreenOnLeftButton();
}

void GameController::onHistoryScreenArrowInputRight(GameModel &model) {
    model.historyScreenOnRightButton();
}

void GameController::onHistoryScreenArrowInput(GameModel &model, const Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onHistoryScreenArrowInputUp(model);
            break;
        case Input::Arrow::Down:
            onHistoryScreenArrowInputDown(model);
            break;
        case Input::Arrow::Left:
            onHistoryScreenArrowInputLeft(model);
            break;
        case Input::Arrow::Right:
            onHistoryScreenArrowInputRight(model);
            break;
    }
}

//**** Char
void GameController::onCharInput0(GameModel &model) {
    if (model.currScreen() == GameScreen::Page::GamePlayHuman) {
        model.deselectCoin();
    }
}

void GameController::onCharInput1(GameModel &model) {
    if (model.currScreen() == GameScreen::Page::GamePlayHuman) {
        model.moveCoinToLeftGroup();
    }
}

void GameController::onCharInput2(GameModel &model) {
    if (model.currScreen() == GameScreen::Page::GamePlayHuman) {
        model.moveCoinToRightGroup();
    }
}

void GameController::onCharInput3(GameModel &model) {
    if (model.currScreen() == GameScreen::Page::GamePlayHuman) {
        model.selectCoinToGuess();
    }
}

void GameController::onReturnButton(GameModel &model) {
    model.mainScreenOnReturnButton();
}

void GameController::onCharInput(GameModel &model, const char charInp) {
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



//***************************************************** Input process function
void GameController::onReceivingInput(GameModel &model, const Input &inp) {
    switch (inp.sourceScreen()) {
        case Input::Source::Main:
            switch (inp.inputType()) {
                case Input::Type::Unknown:
                    break;
                case Input::Type::Char:
                    onCharInput(model, inp.whatChar());
                    break;
                case Input::Type::Arrow:
                    onMainScreenArrowInput(model, inp.whatArrow());
                    break;
            }
            break;
        case Input::Source::History:
            switch (inp.inputType()) {
                case Input::Type::Unknown:
                    break;
                case Input::Type::Char:
                    break;
                case Input::Type::Arrow:
                    onHistoryScreenArrowInput(model, inp.whatArrow());
                    break;
            }
            break;
    }
}
