//
//  player.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#include "player.hpp"
#include "exception.hpp"

//************************** Constructor
Player::Player(const size_t numOfCoins) : selection(numOfCoins), history() {}



//************************** Field accessors
const CoinSelection &Player::currSelection() const {
    return selection;
}

const History &Player::currHistory() const {
    return history;
}

const size_t Player::numOfCoins() const {
    return selection.totalSize();
}



//************************** Coin states manipulation
void Player::setSelectionGroup(const size_t coinIndex, const CoinGroup group) {
    selection.setGroup(coinIndex, group);
}



//************************** On receiving weigh result
void Player::receiveWeighResult(const WeighResult weighResult) {
    addWeighResult(weighResult);
    resetStates();
    afterWeigh(weighResult);
}

void Player::addWeighResult(const WeighResult weighResult) {
    history.add(selection, weighResult);
}

void Player::resetStates() {
    selection.reset();
}



//************************** Player exception
template<> const std::string Exception<Player>::headerMessage() const {
    return "Player: ";
}
