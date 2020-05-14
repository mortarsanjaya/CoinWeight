//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"
#include "gamemodel.hpp"
#include "gameui.hpp"

//************************** Register model
void GameController::registerModel(const std::shared_ptr<GameModel> model) {
    this->model = model;
}

void GameController::registerUI(std::unique_ptr<GameUI> &ui) {
    std::swap(this->view, ui);
}


//************************** Input function
//**** Arrow, Main
void GameController::onButtonUp() {
    model->onUpButton();
}

void GameController::onButtonDown() {
    model->onDownButton();
}

void GameController::onButtonLeft() {
    model->onLeftButton();
}

void GameController::onButtonRight() {
    model->onRightButton();
}

void GameController::onArrowInput(const Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onButtonUp();
            break;
        case Input::Arrow::Down:
            onButtonDown();
            break;
        case Input::Arrow::Left:
            onButtonLeft();
            break;
        case Input::Arrow::Right:
            onButtonRight();
            break;
    }
}



//**** Char
void GameController::onCharInput0() {
    if (model->currScreen().currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->deselectCoin();
    }
}

void GameController::onCharInput1() {
    if (model->currScreen().currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToLeftGroup();
    }
}

void GameController::onCharInput2() {
    if (model->currScreen().currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToRightGroup();
    }
}

void GameController::onCharInput3() {
    if (model->currScreen().currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->selectCoinToGuess();
    }
}

void GameController::onReturnButton() {
    model->onReturnButton();
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
            onArrowInput(inp.whatArrow());
            break;
    }
}

void GameController::receiveInput() {
    view->receiveInput();
}

const Input GameController::lastInput() {
    return view->lastInput();
}



//************************** View update functions
//**** Helper
void GameController::updateViewTitleScreen() {
    view->drawTitleScreen(model->currScreen().titleScreen());
}

void GameController::updateViewInstructionScreen() {
    view->drawInstructionScreen(model->currScreen().instructionScreen());
}

void GameController::updateViewCreditScreen() {
    view->drawCreditScreen(model->currScreen().creditScreen());
}

void GameController::updateViewGameOptionScreen() {
    view->drawGameOptionScreen(model->currScreen().gameOptionScreen());
}

void GameController::updateViewGamePlayHumanScreen() {
    view->drawGamePlayHumanScreen(model->currPlayer()->currSelection(),
        model->currScreen().gamePlayHumanScreen(), model->weighCounter(), model->prevWeighResult());
}

void GameController::updateViewGamePlayComputerScreen() {
    view->drawGamePlayComputerScreen(model->currPlayer()->currSelection(),
        model->currScreen().gamePlayComputerScreen(), model->weighCounter(), model->prevWeighResult());
}

void GameController::updateViewGameOverScreen() {
    view->drawGameOverScreen(model->prevGuessResult(), model->weighCounter());
}

//**** Main
void GameController::updateView() {
    switch (model->currScreen().currentScreen()) {
        case GameScreen::Page::Title:
            updateViewTitleScreen();
            break;
        case GameScreen::Page::Instruction:
            updateViewInstructionScreen();
            break;
        case GameScreen::Page::Credit:
            updateViewCreditScreen();
            break;
        case GameScreen::Page::GameOption:
            updateViewGameOptionScreen();
            break;
        case GameScreen::Page::GamePlayHuman:
            updateViewGamePlayHumanScreen();
            break;
        case GameScreen::Page::GamePlayComputer:
            updateViewGamePlayComputerScreen();
            break;
        case GameScreen::Page::GameOver:
            updateViewGameOverScreen();
            break;
    }
}
