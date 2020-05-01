//
//  computermediumfactory.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-28.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computermediumfactory_hpp
#define computermediumfactory_hpp

#include "computerfactory.hpp"

class ComputerMediumFactory : public ComputerFactory {
public:
    std::unique_ptr<Computer> createComputer(const size_t numOfCoins) override;
};

#endif
