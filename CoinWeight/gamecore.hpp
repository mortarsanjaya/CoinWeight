//
//  gamecores.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecore_hpp
#define gamecore_hpp

#include <memory>
#include "coinset.hpp"
#include "gamelevel.hpp"
#include "coinselection.hpp"
#include "weighresult.hpp"
#include "guessresult.hpp"
#include "weighcounter.hpp"

class GameCore {
	std::unique_ptr<CoinSet> setOfCoins;
	GameLevel level;
    WeighCounter counter;
	
public:
	GameCore(int numOfCoins, GameLevel level);

	const size_t numOfCoins() const;
    const GameLevel gameLevel() const;
    const WeighCounter &weighCounter() const;
 
    // Also decrements weighing counter
    // Throws if the counter's value is 0
    const WeighResult compareWeight(const CoinSelection &weighing);
    const GuessResult guessFakeCoins(const CoinSelection &guess) const;
};

#endif
