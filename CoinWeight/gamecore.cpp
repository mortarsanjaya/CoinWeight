//
//  game.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecore.hpp"

#include "human.hpp"
#include "computerhard.hpp"

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
			return 3 * log_ceil<3>(numOfCoins) + 3;
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
GameCore::GameCore(int numOfCoins, std::unique_ptr<Player> player, Level level) :
	setOfCoins(std::make_unique<CoinSet>(numOfCoins, 2)),
	player(std::move(player)),
	level(level),
	numOfWeighingsCap(maxComparisons(numOfCoins, level))
{}
	


//***************************************************** "Field accessors"
const size_t GameCore::numOfCoins() const { return setOfCoins->size(); }
const size_t GameCore::numOfFakes() const { return setOfCoins->numOfFakes(); }
const size_t GameCore::maxNumOfWeighings() const { return numOfWeighingsCap; }



//***************************************************** Public methods
void GameCore::compareWeight() {
	const Weighing &weighing = player->pickToWeigh();
	const int weighResult = setOfCoins->compareWeight(weighing);
	player->addToHistory(weighing, weighResult);
	player->afterWeigh(weighResult);
}

void GameCore::guessFakes() {
	std::vector<size_t> guess = player->pickGuesses();
	int guessResult = setOfCoins->guessFakes(guess);
	player->afterGuess(guessResult);
	player->clearHistory();
}

const bool GameCore::move() {
	// Initialize by deducing if weighing is allowed, then determine strategy
	bool isWeigh = (player->numOfWeighings() < maxNumOfWeighings());
	if (isWeigh) { isWeigh = player->determineStrategy(); }
	// Execute the move
	if (isWeigh) { compareWeight(); }
	else guessFakes();
	return isWeigh;
}



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

