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
#include "settingsscreen.hpp"
#include "gameplayhuman.hpp"
#include "gameplaycomputer.hpp"
#include "gameover.hpp"

using namespace CoinWeight::X11;

//************************** Factory methods
std::unique_ptr<GameScreenBase>
ScreenFactory::createTitleScreen() {
    return std::make_unique<TitleScreen>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createInstructionScreen() {
    return std::make_unique<InstructionScreen>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createCreditScreen() {
    return std::make_unique<CreditScreen>();
}

std::unique_ptr<GameScreenBase>
ScreenFactory::createGameSettingsScreen() {
    return std::make_unique<SettingsScreen>();
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

