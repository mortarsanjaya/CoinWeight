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
	coins(numOfCoins, true), numOfFakeCoins(numOfFakeCoins)
{
	if (numOfFakeCoins < 0 || numOfFakeCoins > numOfCoins) {
		throw CoinSetFailure("Bad number of fake coins.");
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
const size_t CoinSet::size() const {
    return coins.size();
}

const size_t CoinSet::numOfFakes() const {
    return numOfFakeCoins;
}



//***************************************************** Public methods
const int CoinSet::compareWeight(const CoinStates &weighing) const {
    int leftGroupSize = 0;
    int rightGroupSize = 0;
    int leftGroupNumOfFakes = 0;
    int rightGroupNumOfFakes = 0;
    for (size_t i = 0; i < weighing.size(); ++i) {
        if (weighing.at(i) == CoinStates::LeftGroup) {
            ++leftGroupSize;
            if (!coins.at(i)) {
               ++leftGroupNumOfFakes;
            }
        } else if (weighing.at(i) == CoinStates::RightGroup) {
            ++rightGroupSize;
            if (!coins.at(i)) {
               ++rightGroupNumOfFakes;
            }
        }
    }
    
    if (leftGroupSize > rightGroupSize) {
        return WeighResult::LeftHeavy;
    } else if (leftGroupSize < rightGroupSize) {
        return WeighResult::RightHeavy;
    } else if (leftGroupNumOfFakes > rightGroupNumOfFakes) {
        return WeighResult::RightHeavy;
    } else if (leftGroupNumOfFakes > rightGroupNumOfFakes) {
        return WeighResult::LeftHeavy;
    } else {
        return WeighResult::Balance;
    }
}

const bool CoinSet::guessFakeCoins(const CoinStates &guess) const {
	for (int i = 0; i < guess.size(); ++i) {
        switch (guess.at(i)) {
            case CoinStates::LeftGroup :
            case CoinStates::RightGroup :
                throw CoinSetFailure("Invalid guess.");
                break;
            case CoinStates::NoSelect :
                if (!coins.at(i)) {
                    return false;
                }
                break;
            case CoinStates::Guess :
                if (coins.at(i)) {
                    return false;
                }
                break;
        }
	}
    
    return true;
}



//***************************************************** Coin Set Failure
CoinSetFailure::CoinSetFailure(std::string coreMessage) :
    Exception{coreMessage} {}
    
const std::string CoinSetFailure::headerMessage() const {
    return "Coin Set: ";
}
