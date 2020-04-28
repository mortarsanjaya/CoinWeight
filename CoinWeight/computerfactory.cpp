//
//  computerfactory.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#include "computerfactory.hpp"
#include "computereasyfactory.hpp"
#include "computermediumfactory.hpp"
#include "computerhardfactory.hpp"
#include <utility>

const std::unique_ptr<ComputerFactory> ComputerFactory::createFactory(const GameLevel level) {
    switch (level) {
        case GameLevel::Easy:
            return std::make_unique<ComputerEasyFactory>();
        case GameLevel::Medium:
            return std::make_unique<ComputerMediumFactory>();
        case GameLevel::Hard:
            return std::make_unique<ComputerHardFactory>();
    }
}
