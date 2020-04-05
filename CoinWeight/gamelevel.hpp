//
//  gamelevel.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamelevel_hpp
#define gamelevel_hpp

#include <string>

enum class GameLevel {
    Easy,
    Medium,
    Hard
};

const std::string toString(const GameLevel gameLevel);

#endif
