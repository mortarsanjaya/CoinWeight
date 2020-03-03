//
//  player.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <vector>
#include "weighing.hpp"

class Player {
	size_t coinSetSize;
	size_t numOfFakes;
	std::vector<std::pair<Weighing, int>> history;
	
	
	
public:
	Player(size_t coinSetSize, size_t numOfFakes);
	virtual ~Player();
	
	// Accessor functions
	const size_t numOfCoins() const;
	const size_t numOfFakeCoins() const;
	const size_t numOfWeighings() const;
	const std::vector<std::pair<Weighing, int>> playerHistory() const;
	
	// Determine strategy (and also next move)
	// Returns true if next move is compare weight, false if guessing
	virtual bool determineStrategy() = 0;
	
	// Weighing process
	virtual const Weighing pickToWeigh() const = 0;
	virtual void afterWeigh(const int weighResult) = 0;
	
	// Guessing process
	virtual const std::vector<size_t> pickGuesses() const = 0;
	virtual void afterGuess(const int guessResult) const = 0;
	
	// Adds to the history of players
	void addToHistory(const Weighing &weighing, const int weighResult);
	
	// Clears history
	void clearHistory();
	
	
};

#endif
