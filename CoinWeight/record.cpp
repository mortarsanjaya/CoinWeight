//
//  record.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "record.hpp"

//***************************************************** Constructor
Record::Record(CoinStates weighStates, int weighResult) :
    weighStates{weighStates}, weighResult{weighResult} {}



//***************************************************** Field accessors
const CoinStates Record::coinStates() const {
    return weighStates;
}

const int Record::result() const {
    return weighResult;
}
