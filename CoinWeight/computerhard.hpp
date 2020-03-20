//
//  computerhard.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-23.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computerhard_hpp
#define computerhard_hpp

#include "computer.hpp"
#include <memory>

class ComputerHard : public Computer {

    // States and strategy: How the results are handled
    struct State {
        std::vector<std::vector<size_t>> partition;
        enum class Type;
        Type type;
        State(size_t numOfCoins);
    };
    
    enum class Strategy;
    
    std::unique_ptr<State> state;
    Strategy strategy;
    
    // Modifies partition so it is ready for guessing or weighing
    const Strategy formStrategy();
    
    // Overriding functions
    const Weighing pickToWeigh() const override;
    void afterWeigh(int weighResult) override;
    const std::vector<size_t> pickGuesses() const override;
    
public:
    ComputerHard(size_t numOfCoins, size_t numOfFakeCoins);
    ~ComputerHard();
};

#endif
