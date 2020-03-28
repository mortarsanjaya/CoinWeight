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
#include <string>
#include "coinset.hpp"
#include "coinstates.hpp"
#include "weighresult.hpp"

class GameCore {
public:
	enum class Level { Easy, Medium, Hard };
	
private:
	std::unique_ptr<CoinSet> setOfCoins;
	Level level;
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
	const size_t numOfWeighingsLeft() const;
    const size_t numOfWeighingsCap() const;
 
    // Also adds to the history and decrements weighing counter
    // Throws if the counter's value is 0
    const WeighResult compareWeight(const CoinStates &weighing);
    
    const bool guessFakeCoins(const CoinStates &guess) const;
    
    // Convert a level to a string
    static const std::string levelToString(const Level level);
};

class GameCoreFailure : public Exception {
    const std::string headerMessage() const override;
public:
    GameCoreFailure(std::string coreMessage);
};

#endif
