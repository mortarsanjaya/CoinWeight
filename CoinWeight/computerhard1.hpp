//
//  computerhard1.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computerhard1_hpp
#define computerhard1_hpp

#include "computer.hpp"
#include "range.hpp"
#include "exception.hpp"
#include <memory>

namespace CoinWeight {



class ComputerHard1 final : public Computer {
public:
	ComputerHard1(const size_t numOfCoins);
 
    // Overriding functions
	void setSelection(CoinSelection &selection) const override;
	void changeState(const WeighResult weighResult) override;
 
private:
    class State {
    public:
        virtual ~State() = default;
    
        virtual void setSelection(CoinSelection &selection) const = 0;
        virtual void afterWeigh(ComputerHard1 &computer, const WeighResult weighResult) = 0;
    };
    friend class State;
    
    class OneRange;
    class TwoRanges;
    class Invalid;
    
    const size_t nCoins;
    std::unique_ptr<State> state;
    
    void setOneRangeState(const Range &range);
    void setTwoRangesState(const Range &range1, const Range &range2);
    void setInvalidState();
};



}

#endif
