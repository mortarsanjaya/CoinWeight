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
#include "range.hpp"
#include "exception.hpp"

namespace CoinWeight {



class ComputerMedium1 final : public Computer {
public:
	ComputerMedium1(const size_t numOfCoins);
 
    // Overriding functions
	void setSelection(CoinSelection &selection) const override;
	void changeState(const WeighResult weighResult) override;
 
private:
    struct State {
        enum class Type {
            OneRange,
            TwoRanges0,
            TwoRanges1,
            Finish1Range,
            Finish2Ranges,
            Invalid
        };
        
        Type type;
        Range range1;
        Range range2;
        
        State(const size_t numOfCoins);
    };
    
    const size_t nCoins;
    State state;
    
    const bool readyToGuess() const;
    
    void setSelectionOneRange(CoinSelection &selection) const;
    void setSelectionTwoRanges0(CoinSelection &selection) const;
    void setSelectionTwoRanges1(CoinSelection &selection) const;
    void setSelectionFinish1Range(CoinSelection &selection) const;
    void setSelectionFinish2Ranges(CoinSelection &selection) const;

    void afterWeighLeftHeavy();
    void afterWeighRightHeavy();
    void afterWeighBalance();
    
    void splitCheckLeftHeavyTwoFakes();
    void splitCheckRightHeavyTwoFakes();
    void splitCheckBalanceTwoFakes();
    
    static void splitLeftHeavyOneFake(Range &range);
    static void splitRightHeavyOneFake(Range &range);
    static void splitBalanceOneFake(Range &range);
    void checkRange1OneFake();
    void checkRange2OneFake();
    
    static const size_t splitSize(const Range &range);
    
    static void internalBug() throw (Exception<ComputerMedium1>);
};



};

#endif
