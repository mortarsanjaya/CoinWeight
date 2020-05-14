//
//  computerfactory.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-11.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computerfactory_hpp
#define computerfactory_hpp

#include <memory>
#include "gamelevel.hpp"

class Computer;

class ComputerFactory final {
public:
    static std::unique_ptr<Computer>
    create(const size_t numOfCoins, const size_t numOfMovesMax, const GameLevel level);

private:
    static std::unique_ptr<Computer>
    createEasy(const size_t numOfCoins, const size_t numOfMovesMax);
    
    static std::unique_ptr<Computer>
    createMedium(const size_t numOfCoins, const size_t numOfMovesMax);
    
    static std::unique_ptr<Computer>
    createHard(const size_t numOfCoins, const size_t numOfMovesMax);
};

#endif
