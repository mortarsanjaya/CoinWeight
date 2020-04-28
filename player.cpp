//
//  player.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#include "player.hpp"
#include "computerfactory.hpp"

//************************** Constructor
Player::Player(size_t numOfCoins) : coinStates(numOfCoins), history(), computer() {}
Player::Player(const size_t numOfCoins, const GameLevel gameLevel) :
    coinStates(numOfCoins), history(), computer()
{
    const auto &factory = ComputerFactory::createFactory(gameLevel);
    computer = factory->createComputer(numOfCoins);
}



//************************** Field accessors
const CoinStates &Player::currStates() const {
    return coinStates;
}

const History &Player::currHistory() const {
    return history;
}

const bool Player::isHuman() const {
    return !computer;
}
