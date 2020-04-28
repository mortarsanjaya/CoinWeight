//
//  player.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "coinstates.hpp"
#include "gamelevel.hpp"
#include "history.hpp"
#include <memory>

class Computer;

class Player {
public:
    Player(const size_t numOfCoins);
    Player(const size_t numOfCoins, const GameLevel gameLevel);
    
    const CoinStates &currStates() const;
    const History &currHistory() const;
    const bool isHuman() const;

private:
    CoinStates coinStates;
    History history;
    std::unique_ptr<Computer> computer;
};

#endif
