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

//************************** Constructor
GameController::GameController() {}



//************************** Register model
void GameController::registerModel(const std::shared_ptr<GameModel> model) {
    this->model = model;
}



//************************** Input function
//**** Arrow, Main
void GameController::onScreenArrowInputUp() {
    model->onUpButton();
}

void GameController::onScreenArrowInputDown() {
    model->onDownButton();
}

void GameController::onScreenArrowInputLeft() {
    model->onLeftButton();
}

void GameController::onScreenArrowInputRight() {
    model->onRightButton();
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
            onScreenArrowInput(inp.whatArrow());
            break;
    }
}



//************************** View update functions
//**** Helper
void GameController::updateViewTitleScreen(GameUI *view) {
    view->drawTitleScreen(model->currScreen().titleScreen());
}

void GameController::updateViewInstructionScreen(GameUI *view) {
    view->drawInstructionScreen(model->currScreen().instructionScreen());
}

void GameController::updateViewCreditScreen(GameUI *view) {
    view->drawCreditScreen(model->currScreen().creditScreen());
}

void GameController::updateViewGameOptionScreen(GameUI *view) {
    view->drawGameOptionScreen(model->currScreen().gameOptionScreen());
}

void GameController::updateViewGamePlayHumanScreen(GameUI *view) {
    view->drawGamePlayHumanScreen(model->currPlayer()->currStates(),
        model->currScreen().gamePlayHumanScreen(), model->weighCounter(), model->prevWeighResult());
}

void GameController::updateViewGamePlayComputerScreen(GameUI *view) {
    view->drawGamePlayComputerScreen(model->currPlayer()->currStates(),
        model->currScreen().gamePlayComputerScreen(), model->weighCounter(), model->prevWeighResult());
}

void GameController::updateViewGameOverScreen(GameUI *view) {
    view->drawGameOverScreen(model->prevGuessResult(), model->weighCounter());
}

//**** Main
void GameController::updateView(GameUI *view) {
    switch (model->currScreen().currentScreen()) {
        case GameScreen::Page::Title:
            updateViewTitleScreen(view);
            break;
        case GameScreen::Page::Instruction:
            updateViewInstructionScreen(view);
            break;
        case GameScreen::Page::Credit:
            updateViewCreditScreen(view);
            break;
        case GameScreen::Page::GameOption:
            updateViewGameOptionScreen(view);
            break;
        case GameScreen::Page::GamePlayHuman:
            updateViewGamePlayHumanScreen(view);
            break;
        case GameScreen::Page::GamePlayComputer:
            updateViewGamePlayComputerScreen(view);
            break;
        case GameScreen::Page::GameOver:
            updateViewGameOverScreen(view);
            break;
    }
}
