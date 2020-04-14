//
//  gamecore.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecore.hpp"
#include "exception.hpp"

//***************************************************** Helper functions
// Computes ceiling(log_n k)
template <size_t n> static const size_t log_ceil(size_t k) {
	if (k == 0) exit(100);
	size_t res = 0;
	while (k > 1) {
		k = (k - 1) / n + 1;
		++res;
	}
	return res;
}



//***************************************************** Private static method
const size_t GameCore::maxComparisons(size_t numOfCoins, GameLevel level) {
	switch (level) {
		case GameLevel::Easy:
			return numOfCoins;
		case GameLevel::Medium:
			return 2 * log_ceil<3>(numOfCoins) + 3;
		case GameLevel::Hard:
			return log_ceil<3>(numOfCoins) + log_ceil<3>((numOfCoins + 1) / 2);
	}
}



//***************************************************** Constructor
GameCore::GameCore(int numOfCoins, GameLevel level) :
	setOfCoins(std::make_unique<CoinSet>(numOfCoins)) , level(level),
	numOfWeighingsCounter(maxComparisons(numOfCoins, level)) {}
	


//***************************************************** Field accessors
const size_t GameCore::numOfCoins() const {
    return setOfCoins->size();
}

const GameLevel GameCore::gameLevel() const {
    return level;
}

const size_t GameCore::numOfWeighingsLeft() const {
    return numOfWeighingsCounter;
}

const size_t GameCore::numOfWeighingsCap() const {
    return maxComparisons(setOfCoins->size(), level);
}



//***************************************************** Game operations
const WeighResult GameCore::compareWeight(const CoinStates &weighing) {
    if (numOfWeighingsCounter == 0) {
        throw Exception<GameCore>("No more comparisons.");
    }
    const WeighResult result = setOfCoins->compareWeight(weighing);
    --numOfWeighingsCounter;
    return result;
}

const GuessResult GameCore::guessFakeCoins(const CoinStates &guess) const {
    return setOfCoins->guessFakeCoins(guess);
}



//***************************************************** Game Core Exception header message
template<> const std::string exceptionHeaderMessage<GameCore>() {
    return "Game Core: ";
}
