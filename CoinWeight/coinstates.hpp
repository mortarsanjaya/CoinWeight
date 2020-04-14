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

class CoinStates {
public:
    enum class Value {
        NoSelect,
        LeftGroup,
        RightGroup,
        Guess
    };
    
    CoinStates(size_t numOfCoins);
    
    const size_t size() const;
    const Value at(const size_t index) const;
    
    // Content manipulators
    void deselect(const size_t index);
    void moveToLeftGroup(const size_t index);
    void moveToRightGroup(const size_t index);
    void moveToGuess(const size_t index);
    void resetStates();
    
private:
    std::vector<Value> content;
    size_t leftGroupSize;
    size_t rightGroupSize;
    size_t guessSize;
};

#endif
