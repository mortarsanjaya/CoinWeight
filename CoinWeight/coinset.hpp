//
//  coinset.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coinset_hpp
#define coinset_hpp

#include <vector>
#include <string>
#include "coinstates.hpp"
#include "exception.hpp"

// Fake coins are lighter than real coins
class CoinSet {

	// Set to true if the coin is real and false if the coin is fake
	std::vector<bool> coins;
	size_t numOfFakeCoins;

public:
	// Constructors
	CoinSet(int numOfCoins, int numOfFakeCoins = 2);
	
	// Field accessors
	const size_t size() const;
	const size_t numOfFakes() const;
	
	// Game functions and corresponding enums
    enum WeighResult { LeftHeavy = 1, Balance = 0, RightHeavy = -1 };
	const int compareWeight(const CoinStates &weighing) const;
	const bool guessFakeCoins(const CoinStates &guess) const;
};



//***************************************************** Coin Set Failure
class CoinSetFailure : public Exception {
    const std::string headerMessage() const override;
public:
	CoinSetFailure(std::string coreMessage);
};

#endif
