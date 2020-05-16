//
//  screenfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-15.
//  Copyright © 2020 -. All rights reserved.
//

#include "screenfactory.hpp"

#include "titlescreen.hpp"
#include "instructionscreen.hpp"
#include "creditscreen.hpp"
#include "gamesettingsscreen.hpp"
#include "gameplayhumanscreen.hpp"
#include "gameplaycomputerscreen.hpp"
#include "gameoverscreen.hpp"

//************************** Factory methods
std::unique_ptr<GameScreen>
ScreenFactory::createTitleScreen() {
    return std::make_unique<TitleScreen>();
}

std::unique_ptr<GameScreen>
ScreenFactory::createInstructionScreen() {
    return std::make_unique<InstructionScreen>();
}

std::unique_ptr<GameScreen>
ScreenFactory::createCreditScreen() {
    return std::make_unique<CreditScreen>();
}

std::unique_ptr<GameScreen>
ScreenFactory::createGameSettingsScreen() {
    return std::make_unique<GameSettingsScreen>();
}

std::unique_ptr<GameScreen>
ScreenFactory::createGamePlayHumanScreen(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow)
{
    return std::make_unique<GamePlayHumanScreen>(
        nCoinsTotal, nRowsDisplay, nCoinsPerRow);
}

std::unique_ptr<GameScreen>
ScreenFactory::createGamePlayComputerScreen(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow)
{
    return std::make_unique<GamePlayComputerScreen>(nCoinsTotal,
        nRowsDisplay, nCoinsPerRow);
}

std::unique_ptr<GameScreen>
ScreenFactory::createGameOverScreen(const bool isWin) {
    return std::make_unique<GameOverScreen>(isWin);
}

