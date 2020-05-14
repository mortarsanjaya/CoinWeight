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

class CoinSelection {
public:
    enum class Group {
        NoSelect,
        LeftWeigh,
        RightWeigh,
        Guess
    };

    CoinSelection(size_t numOfCoins);
    
    const size_t totalSize() const;
    const size_t sizeOfLeftWeighGroup() const;
    const size_t sizeOfRightWeighGroup() const;
    const size_t sizeOfGuessGroup() const;
    const Group at(const size_t index) const;
    
    // Content manipulators
    void deselect(const size_t index);
    void moveToLeftWeighGroup(const size_t index);
    void moveToRightWeighGroup(const size_t index);
    void moveToGuessGroup(const size_t index);
    void reset();
    
private:
    std::vector<Group> content;
    size_t leftWeighGroupSize;
    size_t rightWeighGroupSize;
    size_t guessGroupSize;
};

#endif
