//
//  playerfactory.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-08.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef playerfactory_hpp
#define playerfactory_hpp

#include <memory>
#include <utility>
#include "gamelevel.hpp"
#include "humanstd.hpp"
#include "computer.hpp"

class PlayerFactory final {
public:
    static std::unique_ptr<HumanStd>
    createHumanStd(const size_t numOfCoins, const size_t numOfMovesMax);
    
    static std::unique_ptr<Computer>
    createComputer(const size_t numOfCoins, const size_t numOfMovesMax, const GameLevel level);
};

#endif
