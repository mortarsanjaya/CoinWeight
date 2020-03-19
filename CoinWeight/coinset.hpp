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
#include "weighing.hpp"
#include "exception.hpp"

// Fake coins are lighter thhan real coins
class CoinSet {
	// Set to true if the coin is real and false if the coin is fake
	std::vector<bool> coins;
	size_t numOfFakeCoins;

public:
	// Constructors
	CoinSet(int numOfCoins, int numOfFakeCoins = 2);
	
	// Accessor functions
	const size_t size() const;
	const size_t numOfFakes() const;
	
	// Functions that players could use
	
	// Assumes no duplicate values and all indices valid
	// Returns 1 if the first set is heavier than the second set
	// Returns 0 if the first set is as heavy as the second set
	// Returns -1 if the first set is lighter than the second set
	// Note: We assume the fake coins are just a bit lighter than real ones
	//       As a result, bigger sets are always heavier than smaller ones
	// time: O(k), where k = size of set 1 = size of set 2
	//       O(1) if the two sets have different sizes
	const int compareWeight(const Weighing &weighing) const;
	
	// Returns 0 if the player made a correct guess
	// Returns 1 if the player made a valid but wrong guess
	// Returns 2 if the player made an invalid guess
	// time: O(k log k), where k = number of fake coins
	const int guessFakes(std::vector<size_t> guess) const;
};



class CoinSetFailure : public Exception {
    const std::string headerMessage() const override;
public:
	CoinSetFailure(std::string message);
};

#endif
