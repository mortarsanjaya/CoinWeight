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
#include "player.hpp"
#include "gamelevel.hpp"
#include "weighcounter.hpp"

class Computer : public Player {
public:
	virtual ~Computer() = default;
 
    const WeighCounter &weighCounter() const;   
    
protected:
    Computer(const size_t numOfCoins, const size_t numOfMovesMax);
    
    const bool isAbleToWeigh() const final;
    
private:
    WeighCounter counter;
    
    void afterWeigh(const WeighResult weighResult) final;
    
	virtual void setSelection() = 0;
    virtual void changeState(const WeighResult weighResult) = 0;
};

#endif
