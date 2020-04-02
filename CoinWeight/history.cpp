//
//  history.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "history.hpp"

//***************************************************** Field accessors
const size_t History::size() const {
    return listOfRecords.size();
}

const size_t History::currentIndex() const {
    return recordIndex;
}

const Record History::getRecord() const {
    if (listOfRecords.empty()) {
        throw HistoryFailure("History is empty.");
    }
    return listOfRecords[recordIndex];
}

const bool History::empty() const {
    return listOfRecords.empty();
}



//***************************************************** Modifying functions
void History::addRecord(const Record &record) {
    listOfRecords.push_back(record);
}

void History::addRecord(const CoinStates &weighStates, const WeighResult &weighResult) {
    listOfRecords.emplace_back(weighStates, weighResult);
}

void History::clear() {
    listOfRecords.clear();
    recordIndex = 0;
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


//***************************************************** History Failure
HistoryFailure::HistoryFailure(std::string coreMessage) : Exception{coreMessage} {}
const std::string HistoryFailure::headerMessage() const {
    return "History Failure: ";
}
