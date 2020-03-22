//
//  computer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "computer.hpp"

//***************************************************** Constructor and Destructor
Computer::Computer(size_t coinSetSize, size_t numOfFakes) :
	coinSetSize(coinSetSize),
	numOfFakes(numOfFakes)
{}

Computer::~Computer() {}



//***************************************************** Field accessors
const size_t Computer::numOfCoins() const { return coinSetSize; }
const size_t Computer::numOfFakeCoins() const { return numOfFakes; }
