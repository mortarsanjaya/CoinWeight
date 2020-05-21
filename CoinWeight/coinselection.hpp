//
//  coinselection.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coinselection_hpp
#define coinselection_hpp

#include <vector>
#include "coingroup.hpp"

namespace CoinWeight {



class CoinSelection final {
public:
    CoinSelection(const size_t numOfCoins);
    
    const size_t totalSize() const;
    const size_t groupSize(const CoinGroup group) const;
    const size_t sizeOfLeftWeighGroup() const;
    const size_t sizeOfRightWeighGroup() const;
    const size_t sizeOfGuessGroup() const;
    const CoinGroup at(const size_t index) const;
    
    // Content manipulators
    void setGroup(const size_t index, const CoinGroup group);
    void reset();
    
private:
    std::vector<CoinGroup> content;
    size_t groupSizeLeft;
    size_t groupSizeRight;
    size_t groupSizeGuess;
    
    void deselect(const size_t index);
};



};

#endif
