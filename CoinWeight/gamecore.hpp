//
//  gamecores.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecore_hpp
#define gamecore_hpp

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include "coinset.hpp"
#include "weighing.hpp"


// Only supports 2-fake-coins game currently
class GameCore {
public:
	enum class Level { Easy, Medium, Hard, Insane };
	
private:
	std::unique_ptr<CoinSet> setOfCoins;
	Level level;
    std::vector<std::pair<Weighing, int>> history;
	size_t numOfWeighingsCounter;
 
    // maximum number of comparisons, to initialize the cap
    static const size_t maxComparisons(size_t numOfCoins, Level level);
	
public:
	GameCore(int numOfCoins, Level level);
	
	// Field accessors
	const size_t numOfCoins() const;
	const size_t numOfFakes() const;
    const std::vector<std::pair<Weighing, int>> gameHistory() const;
	const size_t numOfWeighingsLeft() const;
 
    // Returns 1 if the first set is heavier than the second set
    // Returns 0 if the first set is as heavy as the second set
    // Returns -1 if the first set is lighter than the second set
    // Also adds to the history and decrements weighing counter
    // Throws if the counter's value is 0
    const int compareWeight(const Weighing &weighing);
    
    // Returns 2 for guesses that does not make sens
    // Example: Number of coins != 2, Out of bound index
    // Otherwise, returns 0 for correct guesses and -1 for incorrect ones
    const int guessFakeCoins(const std::vector<size_t> &guess) const;
};

std::istream &operator>>(std::istream &in, GameCore::Level &level);

#endif
