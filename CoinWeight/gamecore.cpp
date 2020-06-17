//
//  gamecore.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecore.hpp"

#include "gamesinglestd.hpp"
#include "gamesinglecomp.hpp"

using namespace CoinWeight;

//************************** Constructor
GameCore::GameCore(const size_t numOfCoins) :
coinSet(numOfCoins), selection(numOfCoins), isGameOver(false), isPlayerWin(false) {}



//************************** Field accessors
const CoinSelection &GameCore::currSelection() const {
    return selection;
}

const WeighResult GameCore::lastWeighResult() const {
    return lastResult;
}

const bool GameCore::gameOver() const {
    return isGameOver;
}



//************************** Game functions
void GameCore::setSelectionGroup(const size_t index, const CoinGroup group) {
    selection.setGroup(index, group);
}

const bool GameCore::compareWeight() {
    if (!ableToCompareWeight()) return false;
    
    const WeighResult result = coinSet.compareWeight(selection);
    if (result == WeighResult::Invalid) return false;
    
    lastResult = result;
    afterWeigh();
    return true;
}

const bool GameCore::guessFakeCoins() {
    const GuessResult result = coinSet.guessFakeCoins(selection);
    if (result == GuessResult::Invalid) return false;
    isGameOver = true;
    if (result == GuessResult::Correct) {
        isPlayerWin = true;
    }
    
    return true;
}



//************************** Factory
std::unique_ptr<GameCore> GameCore::createGame(const GameSettings &settings) {
    switch (settings.mode) {
        case GameMode::Standard:
            return std::make_unique<GameSingleStd>(settings.nCoins, settings.level);
        case GameMode::Computer:
            return std::make_unique<GameSingleComp>(settings.nCoins, settings.level);
    }
}
