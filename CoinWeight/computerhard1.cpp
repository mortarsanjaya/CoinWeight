//
//  computerhard1.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "computerhard1.hpp"
#include <utility>
#include "exception.hpp"
#include "coinselection.hpp"

using namespace CoinWeight;

//************************** One Range
class ComputerHard1::OneRange final : public ComputerHard1::State {
public:
    OneRange(const Range &range);

private:
    enum class Type {
        FullRange1, // If the first digit of range size base 3 is 2
        FullRange2, // If the first digit of range size base 3 is 1
        LeftHeavy,
        Balance,
        RightHeavy
    };
    
    Type type;
    Range range;

    void setSelection(CoinSelection &selection) const override;
    void afterWeigh(ComputerHard1 &computer, const WeighResult weighResult) override;
    
    // Only to be called when the type is supposed to be Full Range
    void checkFullRange();
    
    // Helper function
    void setSelectionFullRange1Step1(CoinSelection &selection) const;
    void setSelectionFullRange1Step2(CoinSelection &selection) const;
    void setSelectionFullRange2(CoinSelection &selection) const;
    
    void afterWeighFullRange1(ComputerHard1 &computer, const WeighResult weighResult);
    void afterWeighFullRange2(ComputerHard1 &computer, const WeighResult weighResult);
    void afterWeighLeftHeavy(ComputerHard1 &computer, const WeighResult weighResult);
    void afterWeighBalance(ComputerHard1 &computer, const WeighResult weighResult);
    void afterWeighRightHeavy(ComputerHard1 &computer, const WeighResult weighResult);
    
    
    // Calculations for range splitting
    inline const size_t fullRange2SplitSize() const {
        return range.size() / 2;
    }
    
    inline const size_t fullRange1Step1SplitSize() const {
        return (range.size() + 1) / 3;
    }
    
    inline const size_t fullRange1Step2SplitSize() const {
        return range.size() / 3;
    }
};

//**** A small static helper function
// Always returns either 1 or 2, unless the input is 0 (which is never the case here)
static const size_t leftmost_digit_base_3(const size_t k) {
    size_t l = k;
    if (l == 0) return 0;
    while (l >= 3) {
        l /= 3;
    }
    
    return l;
}



ComputerHard1::OneRange::OneRange(const Range &range) :
range(range), type(Type::FullRange1) {
    checkFullRange();
}

//**** Check on full range
void ComputerHard1::OneRange::checkFullRange() {
    if (leftmost_digit_base_3(range.size() - 1) == 1) {
        type = Type::FullRange2;
    }
}



//**** Set selection
void ComputerHard1::OneRange::setSelection(CoinSelection &selection) const {
    switch (type) {
        case Type::FullRange1:
            setSelectionFullRange1Step1(selection);
            break;
        case Type::FullRange2:
            setSelectionFullRange2(selection);
            break;
        case Type::LeftHeavy:
        case Type::Balance:
        case Type::RightHeavy:
            setSelectionFullRange1Step2(selection);
            break;
    }
}

void ComputerHard1::OneRange::setSelectionFullRange1Step1(CoinSelection &selection) const {
    if (range.size() == 2) {
        selection.setGroup(range.begin(), CoinGroup::Guess);
        selection.setGroup(range.begin() + 1, CoinGroup::Guess);
    } else {
        for (size_t i = 0; i < fullRange1Step1SplitSize(); ++i) {
            selection.setGroup(range.begin() + i, CoinGroup::LeftWeigh);
            selection.setGroup(range.end() - 1 - i, CoinGroup::RightWeigh);
        }
    }
}

void ComputerHard1::OneRange::setSelectionFullRange1Step2(CoinSelection &selection) const {
    const size_t prevWeighGroupSize = fullRange1Step1SplitSize();
    if (type == Type::RightHeavy) {
        for (size_t i = 0; i < fullRange1Step2SplitSize(); ++i) {
            selection.setGroup(range.end() - 1 - i, CoinGroup::LeftWeigh);
            selection.setGroup(range.end() - 1 - prevWeighGroupSize - i, CoinGroup::RightWeigh);
        }
    } else {
        for (size_t i = 0; i < fullRange1Step2SplitSize(); ++i) {
            selection.setGroup(range.begin() + i, CoinGroup::LeftWeigh);
            selection.setGroup(range.begin() + prevWeighGroupSize + i, CoinGroup::RightWeigh);
        }
    }
}

void ComputerHard1::OneRange::setSelectionFullRange2(CoinSelection &selection) const {
    for (size_t i = 0; i < fullRange2SplitSize(); ++i) {
        selection.setGroup(range.begin() + i, CoinGroup::LeftWeigh);
        selection.setGroup(range.end() - 1 - i, CoinGroup::RightWeigh);
    }
}



//**** After weigh
void ComputerHard1::OneRange::afterWeigh(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (type) {
        case Type::FullRange1:
            afterWeighFullRange1(computer, weighResult);
            break;
        case Type::FullRange2:
            afterWeighFullRange2(computer, weighResult);
            break;
        case Type::LeftHeavy:
            afterWeighLeftHeavy(computer, weighResult);
            break;
        case Type::Balance:
            afterWeighBalance(computer, weighResult);
            break;
        case Type::RightHeavy:
            afterWeighRightHeavy(computer, weighResult);
            break;
    }
}

void ComputerHard1::OneRange::afterWeighFullRange1(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
            type = Type::LeftHeavy;
            break;
        case WeighResult::Balance:
            type = Type::Balance;
            break;
        case WeighResult::RightHeavy:
            type = Type::RightHeavy;
            break;
    }
}

void ComputerHard1::OneRange::afterWeighFullRange2(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
            range.setLowerBound(range.begin() + fullRange2SplitSize());
            type = Type::FullRange1;
            checkFullRange();
            break;
        case WeighResult::Balance:
            computer.setTwoRangesState(Range(range.begin(), range.begin() + fullRange2SplitSize()),
                                       Range(range.end() - fullRange2SplitSize(), range.end()));
            break;
        case WeighResult::RightHeavy:
            range.setUpperBound(range.end() - fullRange2SplitSize());
            type = Type::FullRange1;
            checkFullRange();
            break;
    }
}

void ComputerHard1::OneRange::afterWeighLeftHeavy(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
        {
            const size_t range1Begin = range.begin() + fullRange1Step1SplitSize();
            computer.setTwoRangesState(Range(range1Begin, range1Begin + range.size() / 3),
                                       Range(range.end() - fullRange1Step1SplitSize(), range.end()));
        }
            break;
        case WeighResult::Balance:
            range.setLowerBound(range.end() - (range.size() + 2) / 3);
            type = Type::FullRange1;
            checkFullRange();
            break;
        case WeighResult::RightHeavy:
            computer.setInvalidState();
            break;
    }
}

void ComputerHard1::OneRange::afterWeighBalance(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
            range.setBounds(range.begin() + fullRange1Step1SplitSize(), range.end() - fullRange1Step1SplitSize());
            type = Type::FullRange1;
            checkFullRange();
            break;
        case WeighResult::Balance:
            if (range.size() % 3 == 2) {
                const size_t fakeCoin1 = range.begin() + range.size() / 3;
                computer.setTwoRangesState(Range(fakeCoin1, fakeCoin1 + 1),
                                           Range(range.end() - fullRange1Step1SplitSize(), range.end()));
            } else {
                computer.setInvalidState();
            }
            break;
        case WeighResult::RightHeavy:
            computer.setTwoRangesState(Range(range.begin(), range.begin() + fullRange1Step2SplitSize()),
                                       Range(range.end() - fullRange1Step1SplitSize(), range.end()));
            break;
    }
}

void ComputerHard1::OneRange::afterWeighRightHeavy(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
        {
            const size_t range1End = range.end() - fullRange1Step1SplitSize();
            computer.setTwoRangesState(Range(range1End - range.size() / 3, range1End),
                                       Range(range.begin(), range.begin() + fullRange1Step1SplitSize()));
        }
            break;
        case WeighResult::Balance:
            range.setUpperBound(range.begin() + (range.size() + 2) / 3);
            type = Type::FullRange1;
            checkFullRange();
            break;
        case WeighResult::RightHeavy:
            computer.setInvalidState();
            break;
    }
}





//************************** Two Ranges
class ComputerHard1::TwoRanges final : public ComputerHard1::State {
public:
    TwoRanges(const Range &range1, const Range &range2);

private:
    enum class Type {
        Range1,
        Range2
    };
    
    Type type;
    Range range1;
    Range range2;

    void setSelection(CoinSelection &selection) const override;
    void afterWeigh(ComputerHard1 &computer, const WeighResult weighResult) override;
    
    void afterWeighCase1(ComputerHard1 &computer, const WeighResult weighResult);
    void afterWeighCase2(ComputerHard1 &computer, const WeighResult weighResult);
    
    inline void checkRange1() {
        if (range1.size() == 1) {
            type = Type::Range2;
        }
    }
};

ComputerHard1::TwoRanges::TwoRanges(const Range &range1, const Range &range2) :
type(Type::Range1), range1(range1), range2(range2) {
    checkRange1();
}



void ComputerHard1::TwoRanges::setSelection(CoinSelection &selection) const {
    if (type == Type::Range1) {
        const size_t weighGroupSize = (range1.size() + 1) / 3;
        for (size_t i = 0; i < weighGroupSize; ++i) {
            selection.setGroup(range1.begin() + i, CoinGroup::LeftWeigh);
            selection.setGroup(range1.end() - 1 - i, CoinGroup::RightWeigh);
        }
    } else if (range2.size() == 1) {
        selection.setGroup(range1.begin(), CoinGroup::Guess);
        selection.setGroup(range2.begin(), CoinGroup::Guess);
    } else {
        const size_t weighGroupSize = (range2.size() + 1) / 3;
        for (size_t i = 0; i < weighGroupSize; ++i) {
            selection.setGroup(range2.begin() + i, CoinGroup::LeftWeigh);
            selection.setGroup(range2.end() - 1 - i, CoinGroup::RightWeigh);
        }
    }
}

void ComputerHard1::TwoRanges::afterWeigh(ComputerHard1 &computer, const WeighResult weighResult) {
    switch (type) {
        case Type::Range1:
            afterWeighCase1(computer, weighResult);
            break;
        case Type::Range2:
            afterWeighCase2(computer, weighResult);
            break;
    }
}

void ComputerHard1::TwoRanges::afterWeighCase1(ComputerHard1 &computer, const WeighResult weighResult) {
    const size_t weighGroupSize = (range1.size() + 1) / 3;
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
            range1.setLowerBound(range1.end() - weighGroupSize);
            break;
        case WeighResult::Balance:
            range1.setBounds(range1.begin() + weighGroupSize, range1.end() - weighGroupSize);
            break;
        case WeighResult::RightHeavy:
            range1.setUpperBound(range1.begin() + weighGroupSize);
            break;
    }
    
    checkRange1();
}

void ComputerHard1::TwoRanges::afterWeighCase2(ComputerHard1 &computer, const WeighResult weighResult) {
    const size_t weighGroupSize = (range2.size() + 1) / 3;
    switch (weighResult) {
        case WeighResult::Start:
        case WeighResult::Invalid:
            computer.setInvalidState();
            break;
        case WeighResult::LeftHeavy:
            range2.setLowerBound(range2.end() - weighGroupSize);
            break;
        case WeighResult::Balance:
            range2.setBounds(range2.begin() + weighGroupSize, range2.end() - weighGroupSize);
            break;
        case WeighResult::RightHeavy:
            range2.setUpperBound(range2.begin() + weighGroupSize);
            break;
    }
}



//************************** Invalid
class ComputerHard1::Invalid final : public ComputerHard1::State {
public:
    Invalid() = default;
    
private:
    void setSelection(CoinSelection &selection) const override {
        selection.setGroup(0, CoinGroup::Guess);
    }
    
    void afterWeigh(ComputerHard1 &computer, const WeighResult weighResult) override {
        throw Exception<ComputerHard1>("Internal bug.");
    }
};
 





//************************** Functions on base Computer Hard
ComputerHard1::ComputerHard1(const size_t numOfCoins) :
nCoins(numOfCoins) {
    setOneRangeState(Range(0, numOfCoins));
}

void ComputerHard1::setSelection(CoinSelection &selection) const {
    state->setSelection(selection);
}

void ComputerHard1::changeState(const WeighResult weighResult) {
    state->afterWeigh(*this, weighResult);
}

void ComputerHard1::setOneRangeState(const Range &range) {
    state = std::make_unique<OneRange>(range);
}

void ComputerHard1::setTwoRangesState(const Range &range1, const Range &range2) {
    state = std::make_unique<TwoRanges>(range1, range2);
}

void ComputerHard1::setInvalidState() {
    state = std::make_unique<Invalid>();
}

