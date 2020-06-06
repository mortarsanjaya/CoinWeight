//
//  movecounter.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-09.
//  Copyright © 2020 -. All rights reserved.
//

#include "weighcounter.hpp"
#include "exception.hpp"

using namespace CoinWeight;

//************************** Constructor
WeighCounter::WeighCounter(const size_t numOfCoins, const GameLevel level) :
nMovesMax(nWeighsCap(numOfCoins, level)), nMovesDone(0) {}



//************************** Field accessors
const size_t WeighCounter::numOfWeighsDone() const {
    return nMovesDone;
}

const size_t WeighCounter::numOfWeighsMax() const {
    return nMovesMax;
}

const bool WeighCounter::isCappedOut() const {
    return (nMovesDone == nMovesMax);
}



//************************** Decrement operator
void WeighCounter::weighingDone() {
    if (isCappedOut()) {
        throw Exception<WeighCounter>("Counter is zero!");
    } else {
        ++nMovesDone;
    }
}



//************************** Cap on the maximum number of weighing
// Computes ceiling(log_base n)
static const size_t log_ceil(const size_t n, const size_t base) {
    if (base <= 1 || n == 0) {
        throw "Input error.";
    }
    
    size_t k = n - 1;
    size_t res = 0;
    while (k > 0) {
        k /= base;
        ++res;
    }
    
    return res;
}


static const size_t nMovesMaxEasy(const size_t numOfCoins) {
    return numOfCoins;
}

static const size_t nMovesMaxMedium(const size_t numOfCoins) {
    return log_ceil(numOfCoins + 1, 2) + log_ceil(numOfCoins + 2, 2) - 3;
}

static const size_t nMovesMaxHard(const size_t numOfCoins) {
    return log_ceil(numOfCoins * (numOfCoins - 1) / 2, 3) + 1;
}

static const size_t nMovesMaxInsane(const size_t numOfCoins) {
    return log_ceil(numOfCoins * (numOfCoins - 1) / 2, 3);
}

//**** Main function
const size_t WeighCounter::nWeighsCap(const size_t numOfCoins, const GameLevel level) {
    switch (level) {
        case GameLevel::Easy:
            return nMovesMaxEasy(numOfCoins);
        case GameLevel::Medium:
            return nMovesMaxMedium(numOfCoins);
        case GameLevel::Hard:
            return nMovesMaxHard(numOfCoins);
    }
}




//************************** Exception header message
template<> const std::string Exception<WeighCounter>::headerMessage() const {
    return "Move Counter: ";
}
