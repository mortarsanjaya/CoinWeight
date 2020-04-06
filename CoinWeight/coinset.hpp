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
#include "coinstates.hpp"
#include "weighresult.hpp"
#include "exception.hpp"

class CoinSet {
    // Fake coins are lighter than real coins and are denoted by [false]
	std::vector<bool> coins;

public:
	CoinSet(int numOfCoins);
    
	const size_t size() const;
	
	// Game operations
	const WeighResult compareWeight(const CoinStates &weighing) const;
	const bool guessFakeCoins(const CoinStates &guess) const;
 
	static const size_t numOfFakeCoins;
};



//***************************************************** Coin Set Failure
class CoinSetFailure : public Exception {
    const std::string headerMessage() const override;
public:
	CoinSetFailure(std::string coreMessage);
};

#endif
