//
//  playerfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-11.
//  Copyright © 2020 -. All rights reserved.
//

#include "playerfactory.hpp"
#include "computerfactory.hpp"

//************************** Factory methods
std::unique_ptr<HumanStd>
PlayerFactory::createHumanStd(const size_t numOfCoins, const size_t numOfMovesMax) {
    return std::make_unique<HumanStd>(numOfCoins, numOfMovesMax);
}

std::unique_ptr<Computer>
PlayerFactory::createComputer(const size_t numOfCoins, const size_t numOfMovesMax, const GameLevel level) {
    return ComputerFactory::create(numOfCoins, numOfMovesMax, level);
}
