//
//  history.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef history_hpp
#define history_hpp

#include <vector>
#include "record.hpp"
#include "exception.hpp"

class History {
    std::vector<Record> listOfRecords;
    size_t recordIndex;
    
    void resetIndex();

public:
    History() = default;
    
    const size_t size() const;
    // Current index is calculated in reverse order of record listing
    const size_t currentIndex() const;
    const Record getRecord() const;
    const bool empty() const;
    
    void addRecord(const Record &record);
    void addRecord(const CoinStates &weighStates, const WeighResult &weighResult);
    void clear();
    void incrementIndex();
    void decrementIndex();
};

class HistoryFailure : public Exception {
    const std::string headerMessage() const override;
public:
    HistoryFailure(std::string coreMessage);
};

#endif
