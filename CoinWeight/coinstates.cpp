//
//  coinstates.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinstates.hpp"
#include "exception.hpp"

//***************************************************** Constructor
CoinStates::CoinStates(size_t numOfCoins) : content(numOfCoins, Value::NoSelect),
    leftGroupSize(0), rightGroupSize(0), guessSize(0)
{}



//***************************************************** Field accessors
const size_t CoinStates::totalSize() const {
    return content.size();
}

const size_t CoinStates::sizeOfLeftGroup() const {
    return leftGroupSize;
}

const size_t CoinStates::sizeOfRightGroup() const {
    return rightGroupSize;
}

const size_t CoinStates::sizeOfGuess() const {
    return guessSize;
}

const CoinStates::Value CoinStates::at(const size_t index) const {
    if (content.size() <= index) {
        throw Exception<CoinStates>("Out of range exception.");
    } else {
        return content.at(index);
    }
}



//***************************************************** Content manipulators
void CoinStates::deselect(const size_t index) {
    switch (at(index)) {
        case Value::NoSelect:
            break;
        case Value::LeftGroup:
            --leftGroupSize;
            break;
        case Value::RightGroup:
            --rightGroupSize;
            break;
        case Value::Guess:
            --guessSize;
            break;
    }
    content[index] = Value::NoSelect;
}

void CoinStates::moveToLeftGroup(const size_t index) {
    deselect(index);
    content[index] = Value::LeftGroup;
    ++leftGroupSize;
}

void CoinStates::moveToRightGroup(const size_t index) {
    deselect(index);
    content[index] = Value::RightGroup;
    ++rightGroupSize;
}

void CoinStates::moveToGuess(const size_t index) {
    deselect(index);
    content[index] = Value::Guess;
    ++guessSize;
}

void CoinStates::resetStates() {
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] = Value::NoSelect;
    }
    
    leftGroupSize = 0;
    rightGroupSize = 0;
    guessSize = 0;
}



//***************************************************** Exception header message
template<> const std::string exceptionHeaderMessage<CoinStates>() {
    return "Coin States Failure: ";
}
