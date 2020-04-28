//
//  coinstates.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinstates.hpp"
#include "exception.hpp"

//************************** Constructor
CoinStates::CoinStates(size_t numOfCoins) : content(numOfCoins, CoinGroup::NoSelect),
    leftWeighGroupSize(0), rightWeighGroupSize(0), guessGroupSize(0)
{}



//************************** Field accessors
const size_t CoinStates::totalSize() const {
    return content.size();
}

const size_t CoinStates::sizeOfLeftWeighGroup() const {
    return leftWeighGroupSize;
}

const size_t CoinStates::sizeOfRightWeighGroup() const {
    return rightWeighGroupSize;
}

const size_t CoinStates::sizeOfGuessGroup() const {
    return guessGroupSize;
}

const CoinGroup CoinStates::at(const size_t index) const {
    if (content.size() <= index) {
        throw Exception<CoinStates>("Out of range exception.");
    } else {
        return content.at(index);
    }
}



//************************** Content manipulators
void CoinStates::deselect(const size_t index) {
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

void CoinStates::moveToLeftWeighGroup(const size_t index) {
    deselect(index);
    content[index] = CoinGroup::LeftWeigh;
    ++leftWeighGroupSize;
}

void CoinStates::moveToRightWeighGroup(const size_t index) {
    deselect(index);
    content[index] = CoinGroup::RightWeigh;
    ++rightWeighGroupSize;
}

void CoinStates::moveToGuessGroup(const size_t index) {
    deselect(index);
    content[index] = CoinGroup::Guess;
    ++guessGroupSize;
}

void CoinStates::resetStates() {
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] = CoinGroup::NoSelect;
    }
    
    leftWeighGroupSize = 0;
    rightWeighGroupSize = 0;
    guessGroupSize = 0;
}



//************************** Exception header message
template<> const std::string exceptionHeaderMessage<CoinStates>() {
    return "Coin States Failure: ";
}
