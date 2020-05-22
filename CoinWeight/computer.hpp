//
//  computer.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computer_hpp
#define computer_hpp

#include <memory>
#include "weighresult.hpp"

namespace CoinWeight {



class CoinSelection;

class Computer {
public:
    Computer() = default;
	virtual ~Computer() = default;
    
    // Computer assumes that the coin selection has the same size as the coin set
    // It also assumes that selection is set at default (all coins NoSelect)
	virtual void setSelection(CoinSelection &selection) const = 0;
    virtual void changeState(const WeighResult weighResult) = 0;
};



};

#endif
