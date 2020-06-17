//
//  gamesinglestd.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesinglestd.hpp"

using namespace CoinWeight;

//******************************** Constructor
GameSingleStd::GameSingleStd(const size_t numOfCoins, const GameLevel level) :
GameCore(numOfCoins), theCounter(numOfCoins, level) {}
    
    
    
//******************************** Field accessors
const WeighCounter &GameSingleStd::counter() const {
    return theCounter;
}



//******************************** Override
const bool GameSingleStd::ableToCompareWeight() const {
    return !theCounter.isCappedOut();
}

void GameSingleStd::afterWeigh() {
    theCounter.weighingDone();
    history.add(selection, lastResult);
    selection.reset();
}
