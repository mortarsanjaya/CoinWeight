//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"

//***************************************************** Input function
//**** Arrow
void GameController::onArrowInputUp() {
    if (model->isOnCoinHighlight()) {
        model->moveCoinHighlightUp();
    } else {
        model->decrementScreenHighlight();
    }
}

void GameController::onArrowInputDown() {
    if (model->isOnCoinHighlight()) {
        model->moveCoinHighlightDown();
    } else {
        model->incrementScreenHighlight();
    }
}

void GameController::onArrowInputLeft() {
    if (model->isOnCoinHighlight()) {
        model->moveCoinHighlightLeft();
    } else if (model->currentScreen() == GameScreen::Page::GameOption) {
        model->decrementScreenHighlight();
    }
}

void GameController::onArrowInputRight() {
    if (model->isOnCoinHighlight()) {
        model->moveCoinHighlightRight();
    } else if (model->currentScreen() == GameScreen::Page::GameOption) {
        model->incrementScreenHighlight();
    }
}

void GameController::onArrowInput(Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onArrowInputUp();
            break;
        case Input::Arrow::Down:
            onArrowInputDown();
            break;
        case Input::Arrow::Left:
            onArrowInputLeft();
            break;
        case Input::Arrow::Right:
            onArrowInputRight();
            break;
    }
}

//**** Char
void GameController::onCharInput0() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->setStateOfCoin(CoinStates::Value::NoSelect);
    }
}

void GameController::onCharInput1() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->setStateOfCoin(CoinStates::Value::LeftGroup);
    }
}

void GameController::onCharInput2() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->setStateOfCoin(CoinStates::Value::RightGroup);
    }
}

void GameController::onCharInput3() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->setStateOfCoin(CoinStates::Value::Guess);
    }
}

void GameController::onCharInput(char charInp) {
    switch (charInp) {
        case 0:
            onCharInput0();
            break;
        case 1:
            onCharInput1();
            break;
        case 2:
            onCharInput2();
            break;
        case 3:
            onCharInput3();
            break;
        default:
            break;
    }
}


//***************************************************** Update view
void GameController::updateView() {
    /*
    switch (model->currentScreen()) {
        case GameScreen::Page::Main:
            view->drawMainScreen(model->screenHighlight());
            break;
        case GameScreen::Page::Instruction:
            view->drawInstructionScreen();
            break;
        case GameScreen::Page::Credit:
            view->drawCreditScreen();
            break;
        case GameScreen::Page::GameOption:
            view->drawGameOptionScreen(model->screenHighlight(), model->gameSize(),
                toString(model->gameLevel()), model->isHumanMode());
            break;
        case GameScreen::Page::GamePlayHuman:
            view->drawGamePlayScreen(model->currentCoinStates(), model->hightlightedCoinIndex(),
                model->numOfWeighingsLeft(), model->numOfWeighingsMax());
            break;
        case GameScreen::Page::GamePlayComputer:
            view->drawGamePlayScreen(model->currentCoinStates(), model->hightlightedCoinIndex(),
                model->numOfWeighingsLeft(), model->numOfWeighingsMax());
            break;
        case GameScreen::Page::GameOver:
            
            break;
    }
    */
}
