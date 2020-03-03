//
//  weighing.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef weighing_hpp
#define weighing_hpp

#include <vector>

// Left group represents the first set, right group represents the second set
struct Weighing {
	std::vector<size_t> leftGroup;
	std::vector<size_t> rightGroup;
	
	Weighing() = default;
};

#endif
