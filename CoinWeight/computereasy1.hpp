//
//  computereasy1.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-29.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computereasy1_hpp
#define computereasy1_hpp

#include "computer.hpp"

class ComputerEasy1 final : public Computer {
public:
	ComputerEasy1(const size_t numOfCoins, const size_t numOfMovesMax);
 
    // Overriding functions
	void setSelection() override;
	void changeState(const WeighResult weighResult) override;
 
private:
    struct State {
        enum class Type {
            FirstMove,
            SecondMove,
            Coin0IsFake,
            Coin0IsReal0,
            Coin0IsReal1,
            Finish
        };
        
        Type type;
        size_t fakeCoin1;
        size_t fakeCoin2;
    };
    
    State state;
    size_t testIndex;
    
    void afterWeighFirstMove(const WeighResult weighResult);
    void afterWeighSecondMove(const WeighResult weighResult);
    void afterWeighCoin0IsFake(const WeighResult weighResult);
    void afterWeighCoin0IsReal0(const WeighResult weighResult);
    void afterWeighCoin0IsReal1(const WeighResult weighResult);
};

#endif
