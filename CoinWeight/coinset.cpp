//
//  coinset.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinset.hpp"
#include "exception.hpp"
#include <random>
#include <algorithm>

//***************************************************** Constructor
CoinSet::CoinSet(int numOfCoins) : numOfCoins{numOfCoins} {
	if (numOfFakeCoins > numOfCoins) {
		throw Exception<CoinSet>("Bad number of fake coins.");
	}
 
    std::random_device seed;
    fakeCoinIndex1 = seed() % numOfCoins;
    fakeCoinIndex2 = seed() % (numOfCoins - 1);
    if (fakeCoinIndex1 > fakeCoinIndex2) {
        std::swap(fakeCoinIndex1, fakeCoinIndex2);
    } else {
        ++fakeCoinIndex2;
    }
}



//***************************************************** Field accessors
const size_t CoinSet::size() const {
    return numOfCoins;
}



//***************************************************** Private member functions
const bool CoinSet::isFakeCoinIndex(const int index) const {
    return ((index == fakeCoinIndex1) || (index == fakeCoinIndex2));
}



//***************************************************** Game operations
const WeighResult CoinSet::compareWeight(const CoinStates &weighing) const {
    int leftGroupSize = 0;
    int rightGroupSize = 0;
    int leftGroupNumOfFakes = 0;
    int rightGroupNumOfFakes = 0;
    for (int i = 0; i < weighing.size(); ++i) {
        if (weighing.at(i) == CoinStates::Value::LeftGroup) {
            ++leftGroupSize;
            if (isFakeCoinIndex(i)) {
               ++leftGroupNumOfFakes;
            }
        } else if (weighing.at(i) == CoinStates::Value::RightGroup) {
            ++rightGroupSize;
            if (isFakeCoinIndex(i)) {
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
                throw Exception<CoinSet>("Invalid guess.");
                break;
            case CoinStates::Value::NoSelect:
                if (isFakeCoinIndex(i)) {
                    return false;
                }
                break;
            case CoinStates::Value::Guess:
                if (isFakeCoinIndex(i)) {
                    return false;
                }
                break;
        }
	}
    
    return true;
}



//***************************************************** Number of fake coins
const size_t CoinSet::numOfFakeCoins = 2;



//***************************************************** Coin Set Exception header message
template<> const std::string exceptionHeaderMessage<CoinSet>() {
    return "Coin Set: ";
}
