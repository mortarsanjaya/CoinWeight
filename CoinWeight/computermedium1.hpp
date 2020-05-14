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

class ComputerMedium1 final : public Computer {
public:
	ComputerMedium1(const size_t numOfCoins, const size_t numOfMovesMax);
 
    // Overriding functions
	void setSelection() override;
	void changeState(const WeighResult weighResult) override;
 
private:
    struct State {
        enum class Type {
            OneRange,
            TwoRanges0,
            TwoRanges1,
            Finish1Range,
            Finish2Ranges
        };
        
        Type type;
        Range range1;
        Range range2;
        
        State(const size_t numOfCoins);
    };
    
    State state;
    
    const bool readyToGuess() const;
    
    void setSelectionOneRange();
    void setSelectionTwoRanges0();
    void setSelectionTwoRanges1();
    void setSelectionFinish1Range();
    void setSelectionFinish2Ranges();

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

#endif
