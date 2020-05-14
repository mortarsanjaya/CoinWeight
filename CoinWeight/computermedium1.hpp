//
//  computermedium1.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef computermedium1_hpp
#define computermedium1_hpp

#include "computer.hpp"

class ComputerMedium1 final : public Computer {
public:
	ComputerMedium1(const size_t numOfCoins);
 
    // Overriding functions
	void beforeWeigh() override;
	void pickToWeigh(CoinSelection &coinStates) const override;
	void afterWeigh(const WeighResult weighResult) override;
	void pickToGuess(CoinSelection &coinStates) const override;
    const bool readyToGuess() const override;
 
private:
    struct State {
        enum class Type {
            OneRange,
            TwoRanges0,
            TwoRanges1,
            Finish
        };
        
        struct Range {
            size_t begin;
            size_t end; // Just like STL iterators
            
            const size_t size() const;
        };
        
        Type type;
        Range range1;
        Range range2;
        
        State(const size_t numOfCoins);
    };
    
    State state;
    
    void pickToWeighOneRange(CoinSelection &coinStates) const;
    void pickToWeighTwoRanges0(CoinSelection &coinStates) const;
    void pickToWeighTwoRanges1(CoinSelection &coinStates) const;
    
    static void pickToWeighPileEndSplit(CoinSelection &coinStates,
        const State::Range &range, const size_t weighPileSize);
    static const size_t weighPileSizeTwoFakes(const State::Range &range);
    static const size_t weighPileSizeOneFake(const State::Range &range);

    void afterWeighLeftHeavy();
    void afterWeighRightHeavy();
    void afterWeighBalance();
    
    void splitCheckLeftHeavyTwoFakes();
    void splitCheckRightHeavyTwoFakes();
    void splitCheckBalanceTwoFakes();
    
    static void splitLeftHeavyOneFake(State::Range &range);
    static void splitRightHeavyOneFake(State::Range &range);
    static void splitBalanceOneFake(State::Range &range);
    void checkRange1OneFake();
    void checkRange2OneFake();
};

#endif
