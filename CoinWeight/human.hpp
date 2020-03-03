//
//  human.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef human_hpp
#define human_hpp

#include "player.hpp"

class Human : public Player {
	bool determineStrategy() override;
	const Weighing pickToWeigh() const override;
	void afterWeigh(const int weighResult) override;
	const std::vector<size_t> pickGuesses() const override;
	void afterGuess(const int guessResult) const override;
	
public:
	Human(size_t numOfCoins, size_t numOfFakeCoins);
	~Human();
};

#endif
