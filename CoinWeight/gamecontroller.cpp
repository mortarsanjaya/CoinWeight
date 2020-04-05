//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"

//***************************************************** Constructor
GameController::GameController(GameModel *model, GameView *view) :
    model{std::unique_ptr<GameModel>(model)}, view{std::unique_ptr<GameView>(view)} {}



//***************************************************** Input function
//**** Arrow, Main
void GameController::onMainScreenArrowInputUp() {
    model->mainScreenOnUpButton();
}

void GameController::onMainScreenArrowInputDown() {
    model->mainScreenOnDownButton();
}

void GameController::onMainScreenArrowInputLeft() {
    model->mainScreenOnLeftButton();
}

void GameController::onMainScreenArrowInputRight() {
    model->mainScreenOnRightButton();
}

void GameController::onMainScreenArrowInput(Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onMainScreenArrowInputUp();
            break;
        case Input::Arrow::Down:
            onMainScreenArrowInputDown();
            break;
        case Input::Arrow::Left:
            onMainScreenArrowInputLeft();
            break;
        case Input::Arrow::Right:
            onMainScreenArrowInputRight();
            break;
    }
}

//**** Arrow, History
void GameController::onHistoryScreenArrowInputUp() {}
void GameController::onHistoryScreenArrowInputDown() {}

void GameController::onHistoryScreenArrowInputLeft() {
    model->historyScreenOnLeftButton();
}

void GameController::onHistoryScreenArrowInputRight() {
    model->historyScreenOnRightButton();
}

void GameController::onHistoryScreenArrowInput(Input::Arrow arrowInp) {
    switch (arrowInp) {
        case Input::Arrow::Up:
            onHistoryScreenArrowInputUp();
            break;
        case Input::Arrow::Down:
            onHistoryScreenArrowInputDown();
            break;
        case Input::Arrow::Left:
            onHistoryScreenArrowInputLeft();
            break;
        case Input::Arrow::Right:
            onHistoryScreenArrowInputRight();
            break;
    }
}

//**** Char
void GameController::onCharInput0() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->deselectCoin();
    }
}

void GameController::onCharInput1() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToLeftGroup();
    }
}

void GameController::onCharInput2() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->moveCoinToRightGroup();
    }
}

void GameController::onCharInput3() {
    if (model->currentScreen() == GameScreen::Page::GamePlayHuman) {
        model->selectCoinToGuess();
    }
}

void GameController::onReturnButton() {
    model->mainScreenOnReturnButton();
}

void GameController::onCharInput(char charInp) {
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


//***************************************************** Update view
void GameController::updateViewOnMainScreen() {
    view->drawMainScreen(model->screenHighlight());
}

void GameController::updateViewOnInstructionScreen() {
    view->drawInstructionScreen();
}

void GameController::updateViewOnCreditScreen() {
    view->drawCreditScreen();
}

void GameController::updateViewOnGameOptionScreen() {
    view->drawGameOptionScreen(model->screenHighlight(), model->gameSize(),
        toString(model->gameLevel()), model->isHumanMode());
}

void GameController::updateViewOnGamePlayHumanScreen() {
    view->drawGamePlayHumanScreen(model->currentCoinStates(), model->screenHighlight(),
        model->hightlightedCoinIndex(), model->numOfWeighingsLeft(), model->numOfWeighingsMax());
    view->drawHistoryScreen(model->currentHistory());
}

void GameController::updateViewOnGamePlayComputerScreen() {
    view->drawGamePlayComputerScreen(model->currentCoinStates(),
        model->numOfWeighingsLeft(), model->numOfWeighingsMax());
    view->drawHistoryScreen(model->currentHistory());
}

void GameController::updateViewOnGameOverScreen() {
    const bool isWin = (model->screenHighlight() == 1);
    view->drawGameOverScreen(isWin, model->numOfWeighingsLeft(), model->numOfWeighingsMax());
}

void GameController::updateView() {
    switch (model->currentScreen()) {
        case GameScreen::Page::Main:
            updateViewOnMainScreen();
            break;
        case GameScreen::Page::Instruction:
            updateViewOnInstructionScreen();
            break;
        case GameScreen::Page::Credit:
            updateViewOnCreditScreen();
            break;
        case GameScreen::Page::GameOption:
            updateViewOnGameOptionScreen();
            break;
        case GameScreen::Page::GamePlayHuman:
            updateViewOnGamePlayHumanScreen();
            break;
        case GameScreen::Page::GamePlayComputer:
            updateViewOnGamePlayComputerScreen();
            break;
        case GameScreen::Page::GameOver:
            updateViewOnGameOverScreen();
            break;
    }
}



//***************************************************** Input process function
void GameController::onReceivingInput(Input inp) {
    switch (inp.sourceScreen()) {
        case Input::Source::Main:
            switch (inp.inputType()) {
                case Input::Type::Unknown:
                    break;
                case Input::Type::Char:
                    onCharInput(inp.whatChar());
                    break;
                case Input::Type::Arrow:
                    onMainScreenArrowInput(inp.whatArrow());
                    break;
            }
            break;
        case Input::Source::History:
            switch (inp.inputType()) {
                case Input::Type::Unknown:
                case Input::Type::Char:
                    break;
                case Input::Type::Arrow:
                    onHistoryScreenArrowInput(inp.whatArrow());
                    break;
            }
            break;
    }
}



//***************************************************** Main function
void GameController::receiveInput() {
    view->receiveInput();
    onReceivingInput(view->lastInput());
}
