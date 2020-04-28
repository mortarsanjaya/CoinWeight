//
//  computerhardfactory0.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-28.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computerhardfactory0_hpp
#define computerhardfactory0_hpp

#include "computerfactory.hpp"

class ComputerHardFactory : public ComputerFactory {
public:
    std::unique_ptr<Computer> createComputer(const size_t numOfCoins) override;
};

#endif
