//
//  gamecores.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecore_hpp
#define gamecore_hpp

#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <string>
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
    
    // Conversion table from a level to a string
    static const std::map<Level, std::string> levelToStringConversionTable;
	
public:
	GameCore(int numOfCoins, Level level);
	
	// Field accessors
	const size_t numOfCoins() const;
	const size_t numOfFakes() const;
    const Level gameLevel() const;
    const std::vector<std::pair<Weighing, int>> gameHistory() const;
	const size_t numOfWeighingsLeft() const;
    const size_t numOfWeighingsCap() const;
 
    // Returns 1 if the first set is heavier than the second set
    // Returns 0 if the first set is as heavy as the second set
    // Returns -1 if the first set is lighter than the second set
    // Also adds to the history and decrements weighing counter
    // Throws if the counter's value is 0
    const int compareWeight(const Weighing &weighing);
    
    // Returns 2 for guesses that does not make sense
    // Example: Number of coins != 2, Out of bound index
    // Otherwise, returns 1 for correct guesses and 0 for incorrect ones
    const int guessFakeCoins(const std::vector<size_t> &guess) const;
    
    // Convert a level to a string
    static const std::string levelToString(const Level level);
};

#endif
