//
//  computer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "computer.hpp"

//***************************************************** Constructor and Destructor
Computer::Computer(size_t coinSetSize) :
	coinSetSize(coinSetSize) {}
    
Computer::~Computer() {}



//***************************************************** Field accessors
const size_t Computer::numOfCoins() const {
    return coinSetSize;
}
