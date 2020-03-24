//
//  coinstates.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coinstates_hpp
#define coinstates_hpp

#include <vector>
#include <string>
#include "exception.hpp"

class CoinStates {
    std::vector<int> content;
public:

    // Constructor
    CoinStates(size_t numOfCoins);
    
    // Field accessors
    const size_t size() const;
    int &operator[](size_t index);
    const int at(size_t index, bool check = true) const;
    
    // enum for coin states
    enum { NoSelect, LeftGroup, RightGroup, Guess };
};

class CoinStatesFailure : public Exception {
    const std::string headerMessage() const override;
public:
    CoinStatesFailure(std::string coreMessage);
};

#endif
