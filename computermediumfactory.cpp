//
//  computermediumfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-28.
//  Copyright © 2020 -. All rights reserved.
//

#include "computermediumfactory.hpp"
#include "computermedium1.hpp"

std::unique_ptr<Computer> ComputerMediumFactory::createComputer(const size_t numOfCoins) {
    return std::make_unique<ComputerMedium1>(numOfCoins);
}
