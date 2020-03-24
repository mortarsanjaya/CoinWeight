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

class Record {
    CoinStates weighStates;
    int weighResult;
    
public:
    Record(CoinStates weighStates, int weighResult);
    // Accessor functions
    const CoinStates coinStates() const;
    const int result() const;
};

#endif
