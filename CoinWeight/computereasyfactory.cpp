//
//  computereasyfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-28.
//  Copyright © 2020 -. All rights reserved.
//

#include "computereasyfactory.hpp"
#include "computerhard.hpp"

std::unique_ptr<Computer> ComputerEasyFactory::createComputer(const size_t numOfCoins) {
    return std::make_unique<ComputerHard>(numOfCoins);
}
