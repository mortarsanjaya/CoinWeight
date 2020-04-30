//
//  computereasyfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-28.
//  Copyright © 2020 -. All rights reserved.
//

#include "computereasyfactory.hpp"
#include "computereasy1.hpp"

std::unique_ptr<Computer> ComputerEasyFactory::createComputer(const size_t numOfCoins) {
    return std::make_unique<ComputerEasy1>(numOfCoins);
}
