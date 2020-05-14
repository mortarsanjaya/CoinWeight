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

class WeighCounter {
public:
    WeighCounter(const size_t numOfMovesMax);
    const size_t numOfWeighsLeft() const;
    const size_t numOfWeighsMax() const;
    const bool isZero() const;
    void decrement();
    

private:
    const size_t nMovesMax;
    size_t nMovesLeft;
};

#endif
