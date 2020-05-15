//
//  coingroup.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef coingroup_h
#define coingroup_h


enum class CoinGroup {
    NoSelect,       // No selection
    LeftWeigh,      // Put to the left scale
    RightWeigh,     // Put to the right scale
    Guess           // Guess as fake coin
};

#endif
