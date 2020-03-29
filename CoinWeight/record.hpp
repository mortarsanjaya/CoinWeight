//
//  record.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef record_hpp
#define record_hpp

#include "coinstates.hpp"
#include "weighresult.hpp"

class Record {
    CoinStates weighStates;
    WeighResult weighResult;
    
public:
    Record(CoinStates weighStates, WeighResult weighResult);
    // Accessor functions
    const CoinStates coinStates() const;
    const WeighResult result() const;
};

#endif
