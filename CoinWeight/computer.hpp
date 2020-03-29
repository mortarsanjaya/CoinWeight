//
//  computer.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computer_hpp
#define computer_hpp

#include <vector>
#include "coinstates.hpp"
#include "weighresult.hpp"

class Computer {
	size_t coinSetSize;
	size_t numOfFakes;
	
public:
	Computer(size_t coinSetSize, size_t numOfFakes = 2);
	virtual ~Computer();
	
	// Accessor functions
	const size_t numOfCoins() const;
	const size_t numOfFakeCoins() const;
	
	// Weighing and guessing process
    virtual void beforeWeigh() = 0;
	virtual const CoinStates pickToWeigh() const = 0;
	virtual void afterWeigh(const WeighResult weighResult) = 0;
	virtual const CoinStates pickToGuess() const = 0;
    virtual const bool readyToGuess() const = 0;
};

#endif
