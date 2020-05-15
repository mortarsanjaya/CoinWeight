//
//  gameview.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameview.hpp"

//************************** Constructor
GameView::GameView(std::unique_ptr<GameUI>ui) :
ui{std::move(ui)} {}



//************************** Drawing functions, passed on to the UI
void GameView::drawTitleScreen(const TitleScreen &screen) {
    ui->drawTitleScreen(screen);
}

void GameView::drawInstructionScreen(const InstructionScreen &screen) {
    ui->drawInstructionScreen(screen);
}

void GameView::drawCreditScreen(const CreditScreen &screen) {
    ui->drawCreditScreen(screen);
}

void GameView::drawGameOptionScreen(const GameOptionScreen &screen) {
    ui->drawGameOptionScreen(screen);
}

void GameView::drawGamePlayHumanScreen(const CoinSelection &selection,
const GamePlayHumanScreen &screen, const WeighCounter &counter,
const WeighResult lastWeighResult) {
    ui->drawGamePlayHumanScreen(selection, screen, counter, lastWeighResult);
}

void GameView::drawGamePlayComputerScreen(const CoinSelection &selection,
const GamePlayComputerScreen &screen, const WeighCounter &counter,
const WeighResult lastWeighResult) {
    ui->drawGamePlayComputerScreen(selection, screen, counter, lastWeighResult);
}

void GameView::drawGameOverScreen(const GuessResult guessResult, const WeighCounter &counter) {
    ui->drawGameOverScreen(guessResult, counter);
}

void GameView::receiveInput() {
    ui->receiveInput();
}

const Input GameView::lastInput() {
    return ui->lastInput();
}
