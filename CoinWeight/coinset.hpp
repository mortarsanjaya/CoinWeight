//
//  coinset.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coinset_hpp
#define coinset_hpp

#include "coinselection.hpp"
#include "gamelevel.hpp"
#include "weighresult.hpp"
#include "guessresult.hpp"

class CoinSet final {
    size_t nCoins;
    size_t fakeCoinI1;
    size_t fakeCoinI2;
    
	static constexpr size_t numOfFakeCoins = 2;
    const bool isFakeCoinIndex(const size_t index) const;

public:
	CoinSet(size_t numOfCoins);
    
	const size_t numOfCoins() const;
    const size_t fakeCoinIndex1() const;
    const size_t fakeCoinIndex2() const;
	
	// Game operations
	const WeighResult compareWeight(const CoinSelection &weighing) const;
	const GuessResult guessFakeCoins(const CoinSelection &guess) const;
 
    friend void computerTest(const size_t nCoinsCap, const GameLevel level);
};

#endif
