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
#include "coinselection.hpp"
#include "weighresult.hpp"

class History final {
public:
    History() = default;
    
    const size_t size() const;
    const bool empty() const;
    const CoinSelection &getSelectionAt(const size_t index) const;
    const WeighResult &getResultAt(const size_t index) const;
    
    void add(const CoinSelection &coinStates, const WeighResult &result);
    void clear();
    
private:
    struct Record {
        CoinSelection coinStates;
        WeighResult result;
    
        Record(const CoinSelection &coinStates, const WeighResult result) :
            coinStates{coinStates}, result{result} {}
    };
    
    std::vector<Record> listOfRecords;
};

#endif
