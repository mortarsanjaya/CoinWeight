//
//  gamesinglecomp.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesinglecomp.hpp"

#include "computerfactory.hpp"

using namespace CoinWeight;

//******************************** Constructor
GameSingleComp::GameSingleComp(const size_t numOfCoins, const GameLevel level) :
GameCore(numOfCoins), theCounter(numOfCoins, level), computer() {
    computer = ComputerFactory::create(numOfCoins, level);
    computerSetup();
}



//******************************** Field accessors
const WeighCounter &GameSingleComp::counter() const {
    return theCounter;
}



//******************************** Override
const bool GameSingleComp::ableToCompareWeight() const {
    return !theCounter.isCappedOut();
}

void GameSingleComp::afterWeigh() {
    theCounter.weighingDone();
    history.add(selection, lastResult);
    selection.reset();
    computerSetup();
}



//******************************** Other
void GameSingleComp::computerSetup() {
    computer->setSelection(selection);
}
