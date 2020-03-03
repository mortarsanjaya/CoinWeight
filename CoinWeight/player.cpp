//
//  player.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "player.hpp"

//***************************************************** Constructor(s) and Destructors
Player::Player(size_t coinSetSize, size_t numOfFakes) :
	coinSetSize(coinSetSize),
	numOfFakes(numOfFakes),
	history()
{}

Player::~Player() {
	clearHistory();
}



//***************************************************** Field accessors
const size_t Player::numOfCoins() const { return coinSetSize; }
const size_t Player::numOfFakeCoins() const { return numOfFakes; }
const size_t Player::numOfWeighings() const { return history.size(); }
const std::vector<std::pair<Weighing, int>> Player::playerHistory() const {
	return history;
}



//***************************************************** Private methods
void Player::clearHistory() { history.clear(); }



//***************************************************** Public methods
void Player::addToHistory(const Weighing &weighing, const int weighResult) {
	history.emplace_back(weighing, weighResult);
}
