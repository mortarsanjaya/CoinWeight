//
//  coinselection.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinselection.hpp"
#include "exception.hpp"

//************************** Constructor
CoinSelection::CoinSelection(const size_t numOfCoins) :
content(numOfCoins, CoinGroup::NoSelect), groupSizeLeft(0),
    groupSizeRight(0), groupSizeGuess(0)
{}



//************************** Field accessors
const size_t CoinSelection::totalSize() const {
    return content.size();
}

const size_t CoinSelection::groupSize(const CoinGroup group) const {
    switch (group) {
        case CoinGroup::NoSelect:
            return content.size() - groupSizeLeft - groupSizeRight - groupSizeGuess;
        case CoinGroup::LeftWeigh:
            return groupSizeLeft;
        case CoinGroup::RightWeigh:
            return groupSizeRight;
        case CoinGroup::Guess:
            return groupSizeGuess;
    }
}

const size_t CoinSelection::sizeOfLeftWeighGroup() const {
    return groupSizeLeft;
}

const size_t CoinSelection::sizeOfRightWeighGroup() const {
    return groupSizeRight;
}

const size_t CoinSelection::sizeOfGuessGroup() const {
    return groupSizeGuess;
}

const CoinGroup CoinSelection::at(const size_t index) const {
    if (content.size() <= index) {
        throw Exception<CoinSelection>("Out of range exception.");
    } else {
        return content.at(index);
    }
}



//************************** Content manipulators
//**** Public
void CoinSelection::setGroup(const size_t index, const CoinGroup group) {
    deselect(index);
    content[index] = group;
    switch (group) {
        case CoinGroup::NoSelect:
            break;
        case CoinGroup::LeftWeigh:
            ++groupSizeLeft;
            break;
        case CoinGroup::RightWeigh:
            ++groupSizeRight;
            break;
        case CoinGroup::Guess:
            ++groupSizeGuess;
            break;
    }
}

void CoinSelection::reset() {
    for (size_t i = 0; i < content.size(); ++i) {
        content[i] = CoinGroup::NoSelect;
    }
    
    groupSizeLeft = 0;
    groupSizeRight = 0;
    groupSizeGuess = 0;
}

//**** Private
void CoinSelection::deselect(const size_t index) {
    switch (content.at(index)) {
        case CoinGroup::NoSelect:
            break;
        case CoinGroup::LeftWeigh:
            --groupSizeLeft;
            break;
        case CoinGroup::RightWeigh:
            --groupSizeRight;
            break;
        case CoinGroup::Guess:
            --groupSizeGuess;
            break;
    }
    content[index] = CoinGroup::NoSelect;
}



//************************** Exception header message
template<> const std::string Exception<CoinSelection>::headerMessage() const {
    return "Coin States Failure: ";
}
