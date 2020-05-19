//
//  computerfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-11.
//  Copyright © 2020 -. All rights reserved.
//

#include "computerfactory.hpp"
#include "computer.hpp"
#include "computereasy1.hpp"
#include "computermedium1.hpp"

//************************** Main factory method
std::unique_ptr<Computer>
ComputerFactory::create(const size_t numOfCoins, const GameLevel level) {
    switch (level) {
        case GameLevel::Easy:
            return createEasy(numOfCoins);
            break;
        case GameLevel::Medium:
            return createMedium(numOfCoins);
            break;
        case GameLevel::Hard:
            return createHard(numOfCoins);
            break;
    }
}



//************************** Level-based factory methods
std::unique_ptr<Computer>
ComputerFactory::createEasy(const size_t numOfCoins) {
    return std::make_unique<ComputerEasy1>(numOfCoins);
}

std::unique_ptr<Computer>
ComputerFactory::createMedium(const size_t numOfCoins) {
    return std::make_unique<ComputerMedium1>(numOfCoins);
}

std::unique_ptr<Computer>
ComputerFactory::createHard(const size_t numOfCoins) {
    throw Exception<ComputerFactory>("Oops. Hard-level computer NOT IMPLEMENTED YET!");
    return std::make_unique<ComputerMedium1>(numOfCoins);
}



//************************** Exception handling
template<> const std::string Exception<ComputerFactory>::headerMessage() const {
    return "Computer Factory: ";
}
