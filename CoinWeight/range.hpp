//
//  range.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-07.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef range_hpp
#define range_hpp

#include <utility>

class Range {
public:
    Range(const size_t lower, const size_t upper);
    
    const size_t begin() const;
    const size_t end() const;
    const size_t size() const;
    
    void setBounds(const size_t lower, const size_t upper);
    void setLowerBound(const size_t lower);
    void setUpperBound(const size_t upper);

private:
    size_t lower;
    size_t upper;
};

#endif
