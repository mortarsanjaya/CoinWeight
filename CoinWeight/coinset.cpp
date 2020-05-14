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

//************************** Constructor
CoinSet::CoinSet(size_t numOfCoins) : nCoins(numOfCoins) {
	if (numOfFakeCoins > numOfCoins) {
		throw Exception<CoinSet>("Bad number of fake coins.");
	}
 
    std::random_device seed;
    fakeCoinI1 = seed() % numOfCoins;
    fakeCoinI2 = seed() % (numOfCoins - 1);
    if (fakeCoinI1 > fakeCoinI2) {
        std::swap(fakeCoinI1, fakeCoinI2);
    } else {
        ++fakeCoinI2;
    }
}



//************************** Field accessors
const size_t CoinSet::numOfCoins() const {
    return nCoins;
}



//************************** Private member functions
const bool CoinSet::isFakeCoinIndex(const size_t index) const {
    return ((index == fakeCoinI1) || (index == fakeCoinI2));
}



//************************** Game operations
const WeighResult CoinSet::compareWeight(const CoinSelection &weighing) const {
    if (weighing.sizeOfGuessGroup() != 0) {
        return WeighResult::Invalid;
    } else if (weighing.sizeOfLeftWeighGroup() > weighing.sizeOfRightWeighGroup()) {
        return WeighResult::LeftHeavy;
    } else if (weighing.sizeOfLeftWeighGroup() < weighing.sizeOfRightWeighGroup()) {
        return WeighResult::RightHeavy;
    } else {
        const CoinSelection::Group fakeCoin1Group = weighing.at(fakeCoinI1);
        const CoinSelection::Group fakeCoin2Group = weighing.at(fakeCoinI2);
        auto groupValue = [](const CoinSelection::Group coinGroup) -> const int {
            switch (coinGroup) {
                case CoinSelection::Group::NoSelect:
                    return 0;
                case CoinSelection::Group::LeftWeigh:
                    return -1;
                case CoinSelection::Group::RightWeigh:
                    return 1;
                case CoinSelection::Group::Guess:
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

const GuessResult CoinSet::guessFakeCoins(const CoinSelection &guess) const {
    if (guess.sizeOfLeftWeighGroup() != 0 || guess.sizeOfRightWeighGroup() != 0) {
        return GuessResult::Invalid;
    } else if (guess.sizeOfGuessGroup() != numOfFakeCoins) {
        return GuessResult::Incorrect;
    } else if (guess.at(fakeCoinI1) != CoinSelection::Group::Guess) {
        return GuessResult::Incorrect;
    } else if (guess.at(fakeCoinI2) != CoinSelection::Group::Guess) {
        return GuessResult::Incorrect;
    } else {
        return GuessResult::Correct;
    }
}



//************************** Exception header message
template<> const std::string Exception<CoinSet>::headerMessage() const {
    return "Coin Set: ";
}
