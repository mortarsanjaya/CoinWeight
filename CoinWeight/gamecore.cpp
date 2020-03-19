//
//  game.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecore.hpp"

//***************************************************** Helper function
// Computes ceiling(log_n k)
template <size_t n> const size_t log_ceil(size_t k) {
	if (k == 0) exit(100);
	size_t res = 0;
	while (k > 1) {
		k = (k - 1) / n + 1;
		++res;
	}
	return res;
}

const size_t GameCore::maxComparisons(size_t numOfCoins, GameCore::Level level) {
	switch (level) {
		case GameCore::Level::Easy:
			return numOfCoins;
		case GameCore::Level::Medium:
			return 2 * log_ceil<3>(numOfCoins) + 3;
		case GameCore::Level::Hard:
			return log_ceil<3>(numOfCoins) + log_ceil<3>((numOfCoins + 1) / 2);
		case GameCore::Level::Insane:
			return log_ceil<3>((numOfCoins * (numOfCoins - 1)) / 2);
		default:
			throw;
	}
}



//***************************************************** Constructor
GameCore::GameCore(int numOfCoins, Level level) :
	setOfCoins(std::make_unique<CoinSet>(numOfCoins, 2)),
	level(level),
	numOfWeighingsCounter(maxComparisons(numOfCoins, level))
{}
	


//***************************************************** Field accessors
const size_t GameCore::numOfCoins() const { return setOfCoins->size(); }
const size_t GameCore::numOfFakes() const { return setOfCoins->numOfFakes(); }
const std::vector<std::pair<Weighing, int>> GameCore::gameHistory() const {
    return history;
}
const size_t GameCore::numOfWeighingsLeft() const { return numOfWeighingsCounter; }



//***************************************************** Other public methods
// ...



//***************************************************** Input operator
std::istream &operator>>(std::istream &in, GameCore::Level &level) {
	std::string lvString;
	while (true) {
		in >> lvString;
		if (lvString == "Easy") {
			level = GameCore::Level::Easy;
			break;
		} else if (lvString == "Medium") {
			level = GameCore::Level::Medium;
			break;
		} else if (lvString == "Hard") {
			level = GameCore::Level::Hard;
			break;
		} else if (lvString == "Insane") {
			level = GameCore::Level::Insane;
			break;
		}
	}
	return in;
}

