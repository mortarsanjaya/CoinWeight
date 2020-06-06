//
//  weighcounter.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-09.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef weighcounter_hpp
#define weighcounter_hpp

#include <utility>
#include "gamelevel.hpp"

namespace CoinWeight {



class WeighCounter {
public:
    WeighCounter(const size_t numOfCoins, const GameLevel level);
    const size_t numOfWeighsDone() const;
    const size_t numOfWeighsMax() const;
    const bool isCappedOut() const;
    void weighingDone();
    
    static const size_t nWeighsCap(const size_t numOfCoins, const GameLevel level);

private:
    const size_t nMovesMax;
    size_t nMovesDone;
};



};

#endif
