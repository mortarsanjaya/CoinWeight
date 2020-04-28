//
//  computerfactory.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computerfactory_hpp
#define computerfactory_hpp

#include "gamelevel.hpp"
#include "computer.hpp"
#include <memory>

class ComputerFactory {
public:
    virtual ~ComputerFactory() = default;
    static const std::unique_ptr<ComputerFactory> createFactory(const GameLevel level);
    virtual std::unique_ptr<Computer> createComputer(const size_t numOfCoins) = 0;
};

#endif
