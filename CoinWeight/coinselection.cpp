//
//  coinstates.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinselection.hpp"
#include "exception.hpp"

//************************** Constructor
CoinSelection::CoinSelection(size_t numOfCoins) : content(numOfCoins, CoinGroup::NoSelect),
    leftWeighGroupSize(0), rightWeighGroupSize(0), guessGroupSize(0)
{}



//************************** Field accessors
const size_t CoinSelection::totalSize() const {
    return content.size();
}

const size_t CoinSelection::sizeOfLeftWeighGroup() const {
    return leftWeighGroupSize;
}

const size_t CoinSelection::sizeOfRightWeighGroup() const {
    return rightWeighGroupSize;
}

const size_t CoinSelection::sizeOfGuessGroup() const {
    return guessGroupSize;
}

const CoinGroup CoinSelection::at(const size_t index) const {
    if (content.size() <= index) {
        throw Exception<CoinSelection>("Out of range exception.");
    } else {
        return content.at(index);
    }
}



//************************** Content manipulators
void CoinSelection::deselect(const size_t index) {
    switch (at(index)) {
        case CoinGroup::NoSelect:
            break;
        case CoinGroup::LeftWeigh:
            --leftWeighGroupSize;
            break;
        case CoinGroup::RightWeigh:
            --rightWeighGroupSize;
            break;
        case CoinGroup::Guess:
            --guessGroupSize;
            break;
    }
    content[index] = CoinGroup::NoSelect;
}

void CoinSelection::moveToLeftWeighGroup(const size_t index) {
    deselect(index);
    content[index] = CoinGroup::LeftWeigh;
    ++leftWeighGroupSize;
}

void CoinSelection::moveToRightWeighGroup(const size_t index) {
    deselect(index);
    content[index] = CoinGroup::RightWeigh;
    ++rightWeighGroupSize;
}

void CoinSelection::moveToGuessGroup(const size_t index) {
    deselect(index);
    content[index] = CoinGroup::Guess;
    ++guessGroupSize;
}

void CoinSelection::reset() {
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] = CoinGroup::NoSelect;
    }
    
    leftWeighGroupSize = 0;
    rightWeighGroupSize = 0;
    guessGroupSize = 0;
}



//************************** Exception header message
template<> const std::string Exception<CoinSelection>::headerMessage() const {
    return "Coin States Failure: ";
}
