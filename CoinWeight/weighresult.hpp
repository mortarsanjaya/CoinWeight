//
//  weighresult.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-25.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef weighresult_hpp
#define weighresult_hpp

#include <string>

enum class WeighResult {
    Balance,
    LeftHeavy,
    RightHeavy
};

const std::string toString(const WeighResult weighResult);

#endif
