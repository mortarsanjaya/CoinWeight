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
public:
	Computer(size_t numOfCoins);
	virtual ~Computer() = default;
	
	// Weighing and guessing process
    virtual void beforeWeigh() = 0;
	virtual void pickToWeigh(CoinStates &coinStates) const = 0;
	virtual void afterWeigh(const WeighResult weighResult) = 0;
	virtual void pickToGuess(CoinStates &coinStates) const = 0;
    virtual const bool readyToGuess() const = 0;
    
protected:
    const size_t nCoins;
};

#endif
