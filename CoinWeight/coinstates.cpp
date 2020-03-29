//
//  coinstates.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-24.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinstates.hpp"

//***************************************************** Constructor
CoinStates::CoinStates(size_t numOfCoins) :
    content(numOfCoins, NoSelect) {}



//***************************************************** Field accessors
const size_t CoinStates::size() const {
    return content.size();
}

int &CoinStates::operator[](size_t index) {
    return content[index];
}

const int CoinStates::at(size_t index, bool check) const {
    if (check && (content.size() <= index)) {
        throw CoinStatesFailure("Out of range exception.");
    } else {
        return content[index];
    }
}



//***************************************************** Coin States Failure
CoinStatesFailure::CoinStatesFailure(std::string coreMessage) :
    Exception(coreMessage) {}
    
const std::string CoinStatesFailure::headerMessage() const {
    return "Coin States Failure: ";
}
