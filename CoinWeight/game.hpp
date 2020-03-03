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
#include "coinset.hpp"
#include "player.hpp"
#include "weighing.hpp"


// Only supports 2-fake-coins game currently
class Game {
public:
	enum class Level { Easy, Medium, Hard, Insane };
	
private:
	std::unique_ptr<CoinSet> setOfCoins;
	std::unique_ptr<Player> player;
	Level level;
	size_t numOfWeighingsCap;
	
public:
	Game(int numOfCoins, std::unique_ptr<Player> player, Level level);
	
	// "Field accessors"
	const size_t numOfCoins() const;
	const size_t numOfFakes() const;
	const size_t maxNumOfWeighings() const;
	
	// calls the function of the same name in CoinSet
	void compareWeight();
	void guessFakes();
	const bool move();
	
	// maximum number of comparisons
	static const size_t maxComparisons(size_t numOfCoins, Level level);
};

std::istream &operator>>(std::istream &in, Game::Level &level);

#endif
