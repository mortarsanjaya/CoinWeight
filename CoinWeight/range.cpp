//
//  range.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-07.
//  Copyright © 2020 -. All rights reserved.
//

#include "range.hpp"
#include "exception.hpp"

//************************** Constructor
Range::Range(const size_t lower, const size_t upper) {
    setBounds(lower, upper);
}



//************************** Field accessors
const size_t Range::begin() const {
    return lower;
}

const size_t Range::end() const {
    return upper;
}

const size_t Range::size() const {
    return upper - lower;
}



//************************** Set new range
void Range::setBounds(const size_t lower, const size_t upper) {
    if (lower > upper) {
        throw Exception<Range>("Your beginning number is greater than the end number.");
    }
    this->lower = lower;
    this->upper = upper;
}

void Range::setLowerBound(const size_t lower) {
    setBounds(lower, this->upper);
}

void Range::setUpperBound(const size_t upper) {
    setBounds(this->lower, upper);
}



//************************** Exception header message
template<> const std::string Exception<Range>::headerMessage() const {
    return "Range Failure: ";
}
