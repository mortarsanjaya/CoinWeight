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
CoinSet::CoinSet(size_t numOfCoins) : numOfCoins(numOfCoins) {
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
const bool CoinSet::isFakeCoinIndex(const size_t index) const {
    return ((index == fakeCoinIndex1) || (index == fakeCoinIndex2));
}



//***************************************************** Game operations
const WeighResult CoinSet::compareWeight(const CoinStates &weighing) const {
    if (weighing.sizeOfGuessGroup() != 0) {
        return WeighResult::Invalid;
    } else if (weighing.sizeOfLeftWeighGroup() > weighing.sizeOfRightWeighGroup()) {
        return WeighResult::LeftHeavy;
    } else if (weighing.sizeOfLeftWeighGroup() < weighing.sizeOfRightWeighGroup()) {
        return WeighResult::RightHeavy;
    } else {
        const CoinGroup fakeCoin1Group = weighing.at(fakeCoinIndex1);
        const CoinGroup fakeCoin2Group = weighing.at(fakeCoinIndex2);
        auto groupValue = [](const CoinGroup coinGroup) -> const int {
            switch (coinGroup) {
                case CoinGroup::NoSelect:
                    return 0;
                case CoinGroup::LeftWeigh:
                    return -1;
                case CoinGroup::RightWeigh:
                    return 1;
                case CoinGroup::Guess:
                    throw Exception<CoinSet>("Coin States incorrect size-of-guess handling.");
            }
        };
        
        const int totalValue = groupValue(fakeCoin1Group) + groupValue(fakeCoin2Group);
        if (totalValue > 0) {
            return WeighResult::LeftHeavy;
        } else if (totalValue < 0) {
            return WeighResult::RightHeavy;
        } else {
            return WeighResult::Balance;
        }
    }
}

const GuessResult CoinSet::guessFakeCoins(const CoinStates &guess) const {
    if (guess.sizeOfLeftWeighGroup() != 0 || guess.sizeOfRightWeighGroup() != 0) {
        return GuessResult::Invalid;
    } else if (guess.sizeOfGuessGroup() != numOfFakeCoins) {
        return GuessResult::Incorrect;
    } else if (guess.at(fakeCoinIndex1) != CoinGroup::Guess) {
        return GuessResult::Incorrect;
    } else if (guess.at(fakeCoinIndex2) != CoinGroup::Guess) {
        return GuessResult::Incorrect;
    } else {
        return GuessResult::Correct;
    }
}



//***************************************************** Exception header message
template<> const std::string exceptionHeaderMessage<CoinSet>() {
    return "Coin Set: ";
}
