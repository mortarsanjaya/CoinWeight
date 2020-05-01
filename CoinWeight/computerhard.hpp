//
//  computerhard.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-23.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computerhard_hpp
#define computerhard_hpp

#include "computer.hpp"
#include <vector>
#include <memory>

class ComputerHard : public Computer {
public:
	ComputerHard(size_t numOfCoins);
	~ComputerHard();
 
    // Overriding functions
	void beforeWeigh() override;
	void pickToWeigh(CoinStates &coinStates) const override;
	void afterWeigh(const WeighResult weighResult) override;
	void pickToGuess(CoinStates &coinStates) const override;
    const bool readyToGuess() const override;
 
private:

	// States and strategy: How the results are handled
    struct State;
	enum class Strategy;
	
	std::unique_ptr<State> state;
	Strategy strategy;
};

#endif
