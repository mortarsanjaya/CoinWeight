//
//  human.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-08.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef human_hpp
#define human_hpp

#include "player.hpp"
#include "weighcounter.hpp"

// Standard human is a move-counted human.

class HumanStd final : public Player {
public:
    HumanStd(const size_t numOfCoins, const size_t numOfMovesMax);
    
    const bool isAbleToWeigh() const final;
    
private:
    WeighCounter counter;
    
    void afterWeigh(const WeighResult weighResult) final;
};

#endif
