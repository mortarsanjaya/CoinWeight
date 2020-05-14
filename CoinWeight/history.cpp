//
//  history.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "history.hpp"
#include "exception.hpp"

//************************** Field accessors
const size_t History::size() const {
    return listOfRecords.size();
}

const size_t History::currentIndex() const {
    return recordIndex;
}

const Record History::getRecord() const {
    if (listOfRecords.empty()) {
        throw Exception<History>("History is empty.");
    }
    return listOfRecords[recordIndex];
}

const bool History::empty() const {
    return listOfRecords.empty();
}



//************************** Modifying functions
void History::resetIndex() {
    recordIndex = size() - 1;
}

void History::addRecord(const Record &record) {
    listOfRecords.push_back(record);
    resetIndex();
}

void History::addRecord(const CoinSelection &weighStates, const WeighResult &weighResult) {
    listOfRecords.emplace_back(weighStates, weighResult);
    resetIndex();
}

void History::clear() {
    listOfRecords.clear();
    resetIndex();
}

void History::incrementIndex() {
    if (recordIndex < listOfRecords.size() - 1) {
        ++recordIndex;
    }
}

void History::decrementIndex() {
    if (recordIndex > 0) {
        --recordIndex;
    }
}


//************************** History Failure
template<> const std::string Exception<History>::headerMessage() const {
    return "History Failure: ";
}
