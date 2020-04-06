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
CoinSet::CoinSet(int numOfCoins) : coins(numOfCoins, true) {
	if (numOfFakeCoins > numOfCoins) {
		throw CoinSetFailure("Bad number of fake coins.");
	}
 
    for (size_t i = 0; i < numOfFakeCoins; ++i) {
        coins[i] = false;
    }
    
    std::shuffle(coins.begin(), coins.end(), std::random_device{});
}



//***************************************************** Field accessors
const size_t CoinSet::size() const {
    return coins.size();
}



//***************************************************** Game operations
const WeighResult CoinSet::compareWeight(const CoinStates &weighing) const {
    int leftGroupSize = 0;
    int rightGroupSize = 0;
    int leftGroupNumOfFakes = 0;
    int rightGroupNumOfFakes = 0;
    for (size_t i = 0; i < weighing.size(); ++i) {
        if (weighing.at(i) == CoinStates::Value::LeftGroup) {
            ++leftGroupSize;
            if (!coins.at(i)) {
               ++leftGroupNumOfFakes;
            }
        } else if (weighing.at(i) == CoinStates::Value::RightGroup) {
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
    } else if (leftGroupNumOfFakes < rightGroupNumOfFakes) {
        return WeighResult::LeftHeavy;
    } else {
        return WeighResult::Balance;
    }
}

const bool CoinSet::guessFakeCoins(const CoinStates &guess) const {
	for (int i = 0; i < guess.size(); ++i) {
        switch (guess.at(i)) {
            case CoinStates::Value::LeftGroup:
            case CoinStates::Value::RightGroup:
                throw CoinSetFailure("Invalid guess.");
                break;
            case CoinStates::Value::NoSelect:
                if (!coins.at(i)) {
                    return false;
                }
                break;
            case CoinStates::Value::Guess:
                if (coins.at(i)) {
                    return false;
                }
                break;
        }
	}
    
    return true;
}



//***************************************************** Number of fake coins
const size_t CoinSet::numOfFakeCoins = 2;



//***************************************************** Coin Set Failure
CoinSetFailure::CoinSetFailure(std::string coreMessage) :
    Exception{coreMessage} {}
    
const std::string CoinSetFailure::headerMessage() const {
    return "Coin Set: ";
}
