//
//  game.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

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
 
    // Other public methods
    
};

std::istream &operator>>(std::istream &in, GameCore::Level &level);

#endif
