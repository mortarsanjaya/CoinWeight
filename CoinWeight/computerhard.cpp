//
//  computer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-23.
//  Copyright © 2020 -. All rights reserved.
//

#include "computerhard.hpp"
#include <vector>

#include <iostream>

/*
Separate documentation for states and strategies (sadly needed):
    
    State consists of partitions of the set of possibly fake coins and also type
    The types are:
    1. Zero Information:
        Partition consists of one set, any two coins from the set may be fake
    2. One Vs One:
        Partition consists of two sets, each with exactly one fake coin
        Any coin from each set could be the single fake coin
        State is programmed such that if at least one set is a singleton, then
            the first set is definitely a singleton
    3. Split 3 Case 1:
        Partition consists of three nearly-balanced sets, say S1, S2, S3
        Either S1 and S2 contains one fake coin each, or S3 contains two fake coins
    4. Split 3 Case 2:
        Partition consists of two sets, the first one contains at least one fake coin
        
    Strategy are determined based on the current state
    The strategies are:
    1. Guess:
        Possible state types: Zero Information, One Vs One
        Guess the fake coins; invoked when the state ensures the fake coins position
        At process of forming strategy, the partition are merged into one set only
    2. One Vs One:
        Possible state types: One Vs One
        Split whichever set that is not singleton yet; the size of partition becomes four
        Then, swap the first and third element to ensure we are comparing the right set
        Possible next state types: One Vs One
    3. Split 2:
        Possible state types: Zero Information
        Split the big set into three, where last one is "leftover"
        Compare the first two sets, then make decisions
        Possible next state types: Zero Information, One Vs One
    4. Split 3 Step 1:
        Possible state types: Zero Information
        Split the big set into three and compare the first two sets
        Possible next state types: Split 3 Case 1, Split 3 Case 2
    5. Split 3 Step 2 Case 1:
        Possible state types: Split 3 Case 1
        Compare S1 and S3, as described by states documentation
        We create the fourth set for storing r remainder coins, where r = n % 3
        Possible next state types: Zero Information, One Vs One
    6. Split 3 Step 2 Case 2:
        Possible state types: Split 3 Case 2
        "Balance out" the two sets by removing at most one coin from one of the sets
        Then, make comparisons
        Possible next state types: Zero Information, One Vs One
 */


//***************************************************** Helper function
template <size_t n> const size_t first_digit_base(const size_t k) {
    size_t res = k;
    while (res >= n) { res /= n; }
    return res;
}



//***************************************************** State and Strategy
enum class ComputerHard::State::Type {
    ZeroInfo,        // Partition consists of one set, all possibilities remain
    OneVsOne,        // Partition consists of two sets, each one fake coins
    Split3Case1,    // Partition consists of three sets, either the first two contains
                    //   one fake coin each, or the third one containss all fake coins
    Split3Case2,    // Partition consists of two sets, the first one has >= 1 fake coin
    SendingMove        // Intermediate step of forming strategy
};

enum class ComputerHard::Strategy {
    Guess,                // Guess
    Split2,                // Split almost equally into two sets then compare
    Split3Step1,        // Split almost equally into three sets then compare
                        // The first and second one has same size
    OneVsOne,            // Special strategy for OneVsOne; second set split by three
    Split3Step2Case1,    // Compare the second and the third set
    Split3Step2Case2,    // Compare the first and the second set
    NoStrategy            // Neutral state
};

ComputerHard::State::State(size_t numOfCoins) :
    partition(), type(Type::ZeroInfo)
{
    std::vector<size_t> setOfCoins;
    for (size_t i = 0; i < numOfCoins; ++i) { setOfCoins.push_back(i); }
    partition.push_back(setOfCoins);
}



//***************************************************** Constructor and Destructor
ComputerHard::ComputerHard(size_t numOfCoins, size_t numOfFakeCoins) :
    Computer(numOfCoins, numOfFakeCoins),
    state(std::make_unique<State>(numOfCoins)),
    strategy(Strategy::NoStrategy)
{}

ComputerHard::~ComputerHard() {}


//***************************************************** Non-overriding functions
const ComputerHard::Strategy ComputerHard::formStrategy() {

    auto splitLastToThree = [this](const size_t twoSetSize) -> void {
        std::vector<size_t> backSet = state->partition.back();
        auto set1bound = backSet.begin() + twoSetSize;
        auto set2bound = set1bound + twoSetSize;
        state->partition.pop_back();
        state->partition.emplace_back(backSet.begin(), set1bound);
        state->partition.emplace_back(set1bound, set2bound);
        state->partition.emplace_back(set2bound, backSet.end());
    };
    
    auto readyToSendMove = [this]() {
        state->type = State::Type::SendingMove;
    };

    switch (state->type) {
        case State::Type::ZeroInfo:
        // Partition consists of one set
        {
            // Just an extra measure of safety?
            if (state->partition.size() != 1) exit(202);
            
            size_t setSize = state->partition[0].size();
            if (setSize == 2) {
                readyToSendMove();
                return Strategy::Guess;
            }
            // Small case removed
            
            if (first_digit_base<3>(setSize - 1) == 1) {
                const size_t pairSize = state->partition[0].size() / 2;
                splitLastToThree(pairSize);
                
                readyToSendMove();
                return Strategy::Split2;
            } else {
                const size_t pairSize = (state->partition[0].size() + 1) / 3;
                splitLastToThree(pairSize);
                
                readyToSendMove();
                return Strategy::Split3Step1;
            }
        }
        case State::Type::OneVsOne:
        // Partition consists of two sets, where the second set is always set to
        //     size greater than one if possible
        {
            // Just an extra measure of safety?
            if (state->partition.size() != 2) exit(203);
            
            if (state->partition[1].size() == 1) {
                readyToSendMove();
                return Strategy::Guess;
            } else {
                const size_t pairSize = (state->partition[1].size() + 2) / 3;
                splitLastToThree(pairSize);
                std::swap(state->partition[0], state->partition[2]);
                
                readyToSendMove();
                return Strategy::OneVsOne;
            }
        }
        case State::Type::Split3Case1:
        // Partition consists of three sets, first two set is of equal size
        // Either this first two contains one fake coin each, or the third one contains two fake coins
        // Change into a set of four, last set for the "remainder" coins (only from S1 or S3)
        // Then, S3 is switched with S2
        {
            // Just an extra measure of safety?
            if (state->partition.size() != 3) exit(204);
            
            const size_t twoSetSize = state->partition[0].size();
            const size_t lastSetSize = state->partition[2].size();
            std::vector<size_t> lastBit;
            if (twoSetSize > lastSetSize) {
                lastBit.push_back(state->partition[0].back());
                state->partition[0].pop_back();
            } else if (twoSetSize < lastSetSize) {
                lastBit.push_back(state->partition[2].back());
                state->partition[2].pop_back();
            }
            
            state->partition.push_back(lastBit);
            std::swap(state->partition[2], state->partition[1]);
            
            readyToSendMove();
            return Strategy::Split3Step2Case1;
        }
        case State::Type::Split3Case2:
        // Partition consists of two sets, where the first set contains at least one fake coin
        // Change into a set of two, last set for the "remainder" coin (if any)
        {
            // Just an extra measure of safety?
            if (state->partition.size() != 2) exit(205);
            
            const size_t firstSetSize = state->partition[0].size();
            const size_t secondSetSize = state->partition[1].size();
            std::vector<size_t> lastBit;
            if (firstSetSize > secondSetSize) {
                lastBit.push_back(state->partition[0].back());
                state->partition[0].pop_back();
            } else if (firstSetSize < secondSetSize) {
                lastBit.push_back(state->partition[1].back());
                state->partition[1].pop_back();
            }

            state->partition.push_back(lastBit);
            
            readyToSendMove();
            return Strategy::Split3Step2Case2;
        }
        default: // Should not happen
            throw;
    }
};



//***************************************************** Overriding functions
const Weighing ComputerHard::pickToWeigh() const {
    return Weighing{state->partition[0], state->partition[1]};
}

void ComputerHard::afterWeigh(const int weighResult) {
    switch (strategy) {
    
        case Strategy::Split2:
            switch (weighResult) {
                case 1:
                {
                    std::vector<size_t> remainderSet = state->partition.back();
                    state->partition[1].insert(state->partition[1].end(),
                        remainderSet.begin(), remainderSet.end());
                    state->partition.pop_back();
                    state->partition.erase(state->partition.begin());
                    state->type = State::Type::ZeroInfo;
                    break;
                }
                case 0:
                {
                    state->partition.pop_back();
                    state->type = State::Type::OneVsOne;
                    break;
                }
                case -1:
                {
                    std::vector<size_t> remainderSet = state->partition.back();
                    state->partition[0].insert(state->partition[0].end(),
                        remainderSet.begin(), remainderSet.end());
                    state->partition.pop_back();
                    state->partition.pop_back();
                    state->type = State::Type::ZeroInfo;
                    break;
                }
                default:
                    throw;
            }
            break;
            
        case Strategy::Split3Step1:
            switch (weighResult) {
                case 1:
                {
                    state->partition.erase(state->partition.begin());
                    state->type = State::Type::Split3Case2;
                    break;
                }
                case 0:
                {
                    state->type = State::Type::Split3Case1;
                    break;
                }
                case -1:
                {
                    state->partition.erase(state->partition.begin() + 1);
                    state->type = State::Type::Split3Case2;
                    break;
                }
                default:
                    throw;
            }
            break;
            
        case Strategy::OneVsOne:
            switch (weighResult) {
                case 1:
                {
                    state->partition.pop_back();
                    state->partition.erase(state->partition.begin());
                    break;
                }
                case 0:
                {
                    state->partition.erase(state->partition.begin() + 1);
                    state->partition.erase(state->partition.begin());
                    break;
                }
                case -1:
                {
                    state->partition.pop_back();
                    state->partition.erase(state->partition.begin() + 1);
                    break;
                }
                default:
                    throw;
            }
            state->type = State::Type::OneVsOne;
            if (state->partition.back().size() == 1) {
                std::swap(state->partition[0], state->partition[1]);
            }
            break;
            
        case Strategy::Split3Step2Case1:
            switch (weighResult) {
                case 1:
                {
                    if ((state->partition.back().size() == 1) &&
                        (state->partition[2].size() == state->partition[0].size()))
                    {
                        size_t singleton = state->partition.back()[0];
                        state->partition[1].emplace_back(singleton);
                    }
                    
                    state->partition.pop_back();
                    state->partition.pop_back();
                    state->partition.erase(state->partition.begin());
                    state->type = State::Type::ZeroInfo;
                    break;
                }
                case 0:
                // The whole set must consist 3q + 2 coins for this to happen
                {
                    state->partition.erase(state->partition.begin() + 1);
                    state->partition.erase(state->partition.begin());
                    std::swap(state->partition[0], state->partition[1]);
                    state->type = State::Type::OneVsOne;
                    break;
                }
                case -1:
                {
                    state->partition.pop_back();
                    state->partition.erase(state->partition.begin() + 1);
                    state->type = State::Type::OneVsOne;
                    break;
                }
                default:
                    throw;
            }
            break;
            
        case Strategy::Split3Step2Case2:
            switch (weighResult) {
                case 1:
                // That means the remainder coin must belong to the first set and is fake...
                {
                    state->partition.erase(state->partition.begin());
                    std::swap(state->partition[0], state->partition[1]);
                    state->type = State::Type::OneVsOne;
                    break;
                }
                case 0:
                {
                    state->partition.pop_back();
                    state->type = State::Type::OneVsOne;
                    break;
                }
                case -1:
                {
                    state->partition.erase(state->partition.begin() + 1);
                    if (state->partition.back().size() == 1) {
                        size_t singleton = state->partition.back()[0];
                        state->partition[0].emplace_back(singleton);
                    }
                    state->partition.pop_back();
                    state->type = State::Type::ZeroInfo;
                    break;
                }
                default:
                    throw;
            }
            break;
            
        default:
            throw;
    }
    
    strategy = Strategy::NoStrategy;
}

const std::vector<size_t> ComputerHard::pickGuesses() const {
    if (state->partition.size() == 2) {
        return std::vector<size_t>{state->partition[0][0], state->partition[1][0]};
    } else {
        return state->partition[0];
    }
}
