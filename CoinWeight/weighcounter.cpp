//
//  movecounter.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-09.
//  Copyright © 2020 -. All rights reserved.
//

#include "weighcounter.hpp"
#include "exception.hpp"

//************************** Constructor
WeighCounter::WeighCounter(const size_t numOfMovesMax) :
nMovesMax(numOfMovesMax), nMovesLeft(numOfMovesMax) {}



//************************** Field accessors
const size_t WeighCounter::numOfWeighsLeft() const {
    return nMovesLeft;
}

const size_t WeighCounter::numOfWeighsMax() const {
    return nMovesMax;
}

const bool WeighCounter::isZero() const {
    return (nMovesLeft == 0);
}



//************************** Decrement operator
void WeighCounter::decrement() {
    if (nMovesLeft == 0) {
        throw Exception<WeighCounter>("Counter is zero!");
    } else {
        --nMovesLeft;
    }
}



//************************** Exception header message
template<> const std::string Exception<WeighCounter>::headerMessage() const {
    return "Move Counter: ";
}
