//
//  modelstatefactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-15.
//  Copyright © 2020 -. All rights reserved.
//

#include "modelstatefactory.hpp"

#include "title.hpp"
#include "instruction.hpp"
#include "credit.hpp"
#include "gamesettings.hpp"
#include "gameplayhuman.hpp"
#include "gameplaycomputer.hpp"
#include "gameover.hpp"

using namespace CoinWeight;

//************************** Factory methods
std::unique_ptr<GameScreenBase>
ScreenFactory::createTitleScreen() {
    return std::make_unique<Title>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createInstructionScreen() {
    return std::make_unique<Instruction>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createCreditScreen() {
    return std::make_unique<Credit>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createGameSettingsScreen() {
    return std::make_unique<GameSettings>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createGamePlayHumanScreen(const size_t nCoinsTotal, const GameLevel level)
{
    return std::make_unique<GamePlayHuman>(nCoinsTotal, level);
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createGamePlayComputerScreen(const size_t nCoinsTotal, const GameLevel level)
{
    return std::make_unique<GamePlayComputer>(nCoinsTotal, level);
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createGameOverScreen(const bool isWin) {
    return std::make_unique<GameOver>(isWin);
}

