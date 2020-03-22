//
//  record.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "record.hpp"

Record::Record(Weighing weighing, int result) : comparedWeight{weighing}, weighResult{result} {}
const Weighing Record::weighing() { return comparedWeight; }
const int Record::result() { return weighResult; }
