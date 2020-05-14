//
//  gamescreen.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamescreen.hpp"
#include "exception.hpp"

//************************** Constructor
GameScreen::GameScreen() : page(Page::Title), title() {}
    


//************************** Field accessors
const GameScreen::Page GameScreen::currentScreen() const {
    return page;
}

const TitleScreen &GameScreen::titleScreen() const {
    if (page != Page::Title) {
        throw Exception<GameScreen>("Currently not a title screen.");
    }
    
    return title;
}

const InstructionScreen &GameScreen::instructionScreen() const {
    if (page != Page::Instruction) {
        throw Exception<GameScreen>("Currently not an instruction screen.");
    }
    
    return instruction;
}

const CreditScreen &GameScreen::creditScreen() const {
    if (page != Page::Credit) {
        throw Exception<GameScreen>("Currently not a credit screen.");
    }
    
    return credit;
}

const GameOptionScreen &GameScreen::gameOptionScreen() const {
    if (page != Page::GameOption) {
        throw Exception<GameScreen>("Currently not a game option screen.");
    }
    
    return gameOption;
}

const GamePlayHumanScreen &GameScreen::gamePlayHumanScreen() const {
    if (page != Page::GamePlayHuman) {
        throw Exception<GameScreen>("Currently not a human game screen.");
    }
    
    return gamePlayHuman;
}

const GamePlayComputerScreen &GameScreen::gamePlayComputerScreen() const {
    if (page != Page::GamePlayComputer) {
        throw Exception<GameScreen>("Currently not a computer game screen.");
    }
    
    return gamePlayComputer;
}

const GameOverScreen &GameScreen::gameOverScreen() const {
    if (page != Page::GameOver) {
        throw Exception<GameScreen>("Currently not a game over screen.");
    }
    
    return gameOver;
}



//************************** Arrow button highlight switch
void GameScreen::highlightUp() {
    switch (page) {
        case Page::Title:
            title.highlightUp();
            break;
        case Page::Instruction:
            instruction.highlightUp();
            break;
        case Page::Credit:
            credit.highlightUp();
            break;
        case Page::GameOption:
            gameOption.highlightUp();
            break;
        case Page::GamePlayHuman:
            gamePlayHuman.highlightUp();
            break;
        case Page::GamePlayComputer:
            gamePlayComputer.highlightUp();
            break;
        case Page::GameOver:
            gameOver.highlightUp();
            break;
    }
}

void GameScreen::highlightDown() {
    switch (page) {
        case Page::Title:
            title.highlightDown();
            break;
        case Page::Instruction:
            instruction.highlightDown();
            break;
        case Page::Credit:
            credit.highlightDown();
            break;
        case Page::GameOption:
            gameOption.highlightDown();
            break;
        case Page::GamePlayHuman:
            gamePlayHuman.highlightDown();
            break;
        case Page::GamePlayComputer:
            gamePlayComputer.highlightDown();
            break;
        case Page::GameOver:
            gameOver.highlightDown();
            break;
    }
}

void GameScreen::highlightLeft() {
    switch (page) {
        case Page::Title:
            title.highlightLeft();
            break;
        case Page::Instruction:
            instruction.highlightLeft();
            break;
        case Page::Credit:
            credit.highlightLeft();
            break;
        case Page::GameOption:
            gameOption.highlightLeft();
            break;
        case Page::GamePlayHuman:
            gamePlayHuman.highlightLeft();
            break;
        case Page::GamePlayComputer:
            gamePlayComputer.highlightLeft();
            break;
        case Page::GameOver:
            gameOver.highlightLeft();
            break;
    }
}

void GameScreen::highlightRight() {
    switch (page) {
        case Page::Title:
            title.highlightRight();
            break;
        case Page::Instruction:
            instruction.highlightRight();
            break;
        case Page::Credit:
            credit.highlightRight();
            break;
        case Page::GameOption:
            gameOption.highlightRight();
            break;
        case Page::GamePlayHuman:
            gamePlayHuman.highlightRight();
            break;
        case Page::GamePlayComputer:
            gamePlayComputer.highlightRight();
            break;
        case Page::GameOver:
            gameOver.highlightRight();
            break;
    }
}



//************************** Reset highlight
void GameScreen::resetHighlight() {
    switch (page) {
        case Page::Title:
            title.resetHighlight();
            break;
        case Page::Instruction:
            instruction.resetHighlight();
            break;
        case Page::Credit:
            credit.resetHighlight();
            break;
        case Page::GameOption:
            gameOption.resetHighlight();
            break;
        case Page::GamePlayHuman:
            gamePlayHuman.resetHighlight();
            break;
        case Page::GamePlayComputer:
            gamePlayComputer.resetHighlight();
            break;
        case Page::GameOver:
            gameOver.resetHighlight();
            break;
    }
}



//************************** Screen switch
void GameScreen::goToTitleScreen() {
    page = Page::Title;
    title = TitleScreen();
}

void GameScreen::goToInstructionScreen() {
    page = Page::Instruction;
    instruction = InstructionScreen();
}

void GameScreen::goToCreditScreen() {
    page = Page::Credit;
    credit = CreditScreen();
}

void GameScreen::goToGameOptionScreen() {
    page = Page::GameOption;
    gameOption = GameOptionScreen();
}

void GameScreen::goToGamePlayHumanScreen(const size_t numOfCoins, const size_t coinsPerRow) {
    page = Page::GamePlayHuman;
    gamePlayHuman = GamePlayHumanScreen(numOfCoins, coinsPerRow);
}

void GameScreen::goToGamePlayComputerScreen() {
    page = Page::GamePlayComputer;
    gamePlayComputer = GamePlayComputerScreen();
}

void GameScreen::goToGameOverScreen() {
    page = Page::GameOver;
    gameOver = GameOverScreen();
}


//***************************************************** Game Screen Exception header message
template<> const std::string Exception<GameScreen>::headerMessage() const {
    return "Game Screen: ";
}
