//
//  history.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "history.hpp"

using namespace CoinWeight;

//************************** Field accessors
const size_t History::size() const {
    return listOfRecords.size();
}

const bool History::empty() const {
    return listOfRecords.empty();
}

const CoinSelection &History::getSelectionAt(const size_t index) const {
    return listOfRecords.at(index).selection;
}

const WeighResult &History::getResultAt(const size_t index) const {
    return listOfRecords.at(index).result;
}



//************************** Modifying functions
void History::add(const CoinSelection &selection, const WeighResult &result) {
    listOfRecords.emplace_back(selection, result);
}

void History::clear() {
    listOfRecords.clear();
}
