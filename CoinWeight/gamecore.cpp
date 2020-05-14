//
//  gamecore.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecore.hpp"
#include "exception.hpp"
#include "numofweighsmax.hpp"

//************************** Constructor
GameCore::GameCore(int numOfCoins, GameLevel level) :
	setOfCoins(std::make_unique<CoinSet>(numOfCoins)) , level(level),
	counter(numOfWeighsMax(numOfCoins, level)) {}
	


//************************** Field accessors
const size_t GameCore::numOfCoins() const {
    return setOfCoins->numOfCoins();
}

const GameLevel GameCore::gameLevel() const {
    return level;
}

const WeighCounter &GameCore::weighCounter() const {
    return counter;
}



//************************** Game operations
const WeighResult GameCore::compareWeight(const CoinSelection &weighing) {
    if (counter.isZero()) {
        return WeighResult::Invalid;
    }
    
    const WeighResult result = setOfCoins->compareWeight(weighing);
    if (result != WeighResult::Invalid) {
        counter.decrement();
    }
    
    return result;
}

const GuessResult GameCore::guessFakeCoins(const CoinSelection &guess) const {
    return setOfCoins->guessFakeCoins(guess);
}
