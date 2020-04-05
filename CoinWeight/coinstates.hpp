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
public:
    enum class Value {
        NoSelect,
        LeftGroup,
        RightGroup,
        Guess
    };
    
private:
    std::vector<Value> content;
    
public:
    CoinStates(size_t numOfCoins);
    
    const size_t size() const;
    Value &operator[](size_t index);
    const Value at(size_t index) const;
    
    // Resets all states to NoSelect
    void resetStates();
};

class CoinStatesFailure : public Exception {
    const std::string headerMessage() const override;
public:
    CoinStatesFailure(std::string coreMessage);
};

#endif
