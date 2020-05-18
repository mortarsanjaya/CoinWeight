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
std::unique_ptr<ModelState>
ScreenFactory::createTitleScreen() {
    return std::make_unique<Title>();
}

std::unique_ptr<ModelState>
ScreenFactory::createInstructionScreen() {
    return std::make_unique<Instruction>();
}

std::unique_ptr<ModelState>
ScreenFactory::createCreditScreen() {
    return std::make_unique<Credit>();
}

std::unique_ptr<ModelState>
ScreenFactory::createGameSettingsScreen() {
    return std::make_unique<GameSettings>();
}

std::unique_ptr<ModelState>
ScreenFactory::createGamePlayHumanScreen(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow)
{
    return std::make_unique<GamePlayHuman>(
        nCoinsTotal, nRowsDisplay, nCoinsPerRow);
}

std::unique_ptr<ModelState>
ScreenFactory::createGamePlayComputerScreen(const size_t nCoinsTotal,
    const size_t nRowsDisplay, const size_t nCoinsPerRow)
{
    return std::make_unique<GamePlayComputer>(nCoinsTotal,
        nRowsDisplay, nCoinsPerRow);
}

std::unique_ptr<ModelState>
ScreenFactory::createGameOverScreen(const bool isWin) {
    return std::make_unique<GameOver>(isWin);
}

