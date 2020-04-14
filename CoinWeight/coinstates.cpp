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
CoinStates::CoinStates(size_t numOfCoins) : content(numOfCoins, Group::NoSelect),
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

const CoinStates::Group CoinStates::at(const size_t index) const {
    if (content.size() <= index) {
        throw Exception<CoinStates>("Out of range exception.");
    } else {
        return content.at(index);
    }
}



//***************************************************** Content manipulators
void CoinStates::deselect(const size_t index) {
    switch (at(index)) {
        case Group::NoSelect:
            break;
        case Group::LeftGroup:
            --leftGroupSize;
            break;
        case Group::RightGroup:
            --rightGroupSize;
            break;
        case Group::Guess:
            --guessSize;
            break;
    }
    content[index] = Group::NoSelect;
}

void CoinStates::moveToLeftGroup(const size_t index) {
    deselect(index);
    content[index] = Group::LeftGroup;
    ++leftGroupSize;
}

void CoinStates::moveToRightGroup(const size_t index) {
    deselect(index);
    content[index] = Group::RightGroup;
    ++rightGroupSize;
}

void CoinStates::moveToGuess(const size_t index) {
    deselect(index);
    content[index] = Group::Guess;
    ++guessSize;
}

void CoinStates::resetStates() {
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] = Group::NoSelect;
    }
    
    leftGroupSize = 0;
    rightGroupSize = 0;
    guessSize = 0;
}



//***************************************************** Exception header message
template<> const std::string exceptionHeaderMessage<CoinStates>() {
    return "Coin States Failure: ";
}
