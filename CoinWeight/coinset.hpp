//
//  coinset.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coinset_hpp
#define coinset_hpp

#include "coinstates.hpp"
#include "weighresult.hpp"

class CoinSet {
    size_t numOfCoins;
    size_t fakeCoinIndex1;
    size_t fakeCoinIndex2;
    
    const bool isFakeCoinIndex(const size_t index) const;

public:
	CoinSet(size_t numOfCoins);
    
	const size_t size() const;
	
	// Game operations
	const WeighResult compareWeight(const CoinStates &weighing) const;
	const bool guessFakeCoins(const CoinStates &guess) const;
 
	static const size_t numOfFakeCoins;
};

#endif
