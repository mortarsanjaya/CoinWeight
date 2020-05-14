//
//  computer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-11.
//  Copyright © 2020 -. All rights reserved.
//

#include "computer.hpp"

//************************** Constructor
Computer::Computer(const size_t numOfCoins, const size_t numOfMovesMax) :
Player{numOfCoins}, counter{numOfMovesMax} {}



//************************** Non-virtual functions
const bool Computer::isAbleToWeigh() const {
    return !counter.isZero();
}

void Computer::afterWeigh(const WeighResult weighResult) {
    counter.decrement();
    changeState(weighResult);
    setSelection();
}
