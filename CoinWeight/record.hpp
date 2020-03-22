//
//  record.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef record_hpp
#define record_hpp

#include "weighing.hpp"

class Record {
    Weighing comparedWeight;
    int weighResult;
    
public:
    Record(Weighing weighing, int result);
    // Accessor functions
    const Weighing weighing();
    const int result();
};

#endif
