//
//  gamesettings.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesettings_hpp
#define gamesettings_hpp

#include <utility>
#include "gamelevel.hpp"
#include "gamemode.hpp"

namespace CoinWeight {
  


struct GameSettings {
    size_t nCoins;
    GameLevel level;
    GameMode mode;
};



}

#endif
