//
//  numofweighsmax.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-11.
//  Copyright © 2020 -. All rights reserved.
//

#include "numofweighsmax.hpp"

//************************** Helper functions
// Computes ceiling(log_base n)
static const size_t log_ceil(const size_t n, const size_t base) {
    if (base <= 1 || n == 0) {
        throw "Input error.";
    }
    
    size_t k = n - 1;
    size_t res = 0;
    while (k > 0) {
        k /= n;
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


//************************** Main function
const size_t numOfWeighsMax(const size_t numOfCoins, const GameLevel level) {
    switch (level) {
        case GameLevel::Easy:
            return nMovesMaxEasy(numOfCoins);
            break;
        case GameLevel::Medium:
            return nMovesMaxMedium(numOfCoins);
            break;
        case GameLevel::Hard:
            return nMovesMaxHard(numOfCoins);
            break;
    }
}


