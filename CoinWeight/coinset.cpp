//
//  coinset.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinset.hpp"
#include <random>
#include <algorithm>



//***************************************************** Constructor
CoinSet::CoinSet(int numOfCoins, int numOfFakeCoins) :
	coins(numOfCoins, true),
	numOfFakeCoins(numOfFakeCoins)
{
	if (numOfFakeCoins < 0 || numOfFakeCoins > numOfCoins) {
		throw CoinSetFailure("Bad number of fake coins: " +
							std::to_string(numOfFakeCoins) +
							" out of " + std::to_string(numOfCoins));
	}

	std::vector<size_t> fake_coins_position(0);
	for (size_t i = 0; i < numOfFakeCoins; ++i) {
		std::random_device seed;
		size_t one_fake_pos = seed() % (numOfCoins - i);
		for (size_t &prev_fake_pos : fake_coins_position) {
			if (prev_fake_pos > one_fake_pos) break;
			++one_fake_pos;
		}
		fake_coins_position.push_back(one_fake_pos);
		coins[one_fake_pos] = false;
	}
}



//***************************************************** Field accessors
const size_t CoinSet::size() const { return coins.size(); }
const size_t CoinSet::numOfFakes() const { return numOfFakeCoins; }



//***************************************************** Public methods
const int CoinSet::compareWeight(const Weighing &weighing) const {
	auto weight1 = weighing.leftGroup;
	auto weight2 = weighing.rightGroup;
	if (weight1.size() > weight2.size()) return 1;
	if (weight1.size() < weight2.size()) return -1;
	// Number of fake coins in the first set - second set
	int diffOfFakeCoins = 0;
	for (size_t i = 0; i < weight1.size(); ++i) {
		if (!coins[weight1[i]]) ++diffOfFakeCoins;
		if (!coins[weight2[i]]) --diffOfFakeCoins;
	}
	
	if (diffOfFakeCoins > 0) return -1;
	if (diffOfFakeCoins < 0) return 1;
	return 0;
}

const int CoinSet::guessFakes(std::vector<size_t> guess) const {
	if (guess.size() != numOfFakeCoins) return 2; // wrong number of coins to guess
	std::sort(guess.begin(), guess.end());
	for (int i = 0; i < guess.size(); ++i) {
		if (guess[i] >= coins.size()) return 2; // index out of bound; invalid
		if (i < guess.size() - 1 && guess[i] == guess[i + 1]) return 2; // duplicate guess; invalid
	}
	// Otherwise, valid guess; check correctness
	for (int i = 0; i < guess.size(); ++i) {
		if (coins[guess[i]]) return 0; // wrong guess
	}
	return 1;
}



//***************************************************** Coin Set Failure
CoinSetFailure::CoinSetFailure(std::string message) : Exception{message} {}
const std::string CoinSetFailure::headerMessage() const {
    return "Coin Set";
}
