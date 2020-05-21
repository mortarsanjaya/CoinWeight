//
//  coingroup.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coingroup_h
#define coingroup_h

namespace CoinWeight {



enum class CoinGroup {
    NoSelect,       // Not selected
    LeftWeigh,      // Put to left scale
    RightWeigh,     // Put to right scale
    Guess           // Guess as fake coin
};



};

#endif
