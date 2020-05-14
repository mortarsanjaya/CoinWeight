//
//  human.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-08.
//  Copyright © 2020 -. All rights reserved.
//

#include "humanstd.hpp"

//************************** Constructor
HumanStd::HumanStd(const size_t numOfCoins, const size_t numOfMovesMax) :
Player(numOfCoins), counter(numOfMovesMax) {}



//************************** Check if able to weigh
const bool HumanStd::isAbleToWeigh() const {
    return (!counter.isZero());
}



//************************** After weigh method
void HumanStd::afterWeigh(const WeighResult weighResult) {
    counter.decrement();
}




