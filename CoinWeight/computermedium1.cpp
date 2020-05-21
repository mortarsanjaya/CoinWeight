//
//  computermedium1.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "computermedium1.hpp"
#include "coinselection.hpp"
#include "exception.hpp"

/*
Small documentation for the computer strategy:
The computer divides the pile into half (rounded down)
This makes two main piles consisting of about half the total number of coins
    with possibly one coin remaining
The heavier among the two piles must only contain real coins
Otherwise, both piles contain one fake coin (and the remaining coin is real, if any)

The State::Range implements the coin index range for each pile
For Finish-type State from OneRange, put the second fake coin into range 2
 */
 
 using namespace CoinWeight;

//************************** Constructor (+ State)
ComputerMedium1::ComputerMedium1(const size_t numOfCoins) :
Computer{}, nCoins{numOfCoins}, state{numOfCoins} {}

ComputerMedium1::State::State(const size_t numOfCoins) :
type{Type::OneRange}, range1{0, numOfCoins}, range2{0, 0} {}



//************************** Overriding functions
void ComputerMedium1::setSelection(CoinSelection &selection) const {
    switch (state.type) {
        case State::Type::OneRange:
            setSelectionOneRange(selection);
            break;
        case State::Type::TwoRanges0:
            setSelectionTwoRanges0(selection);
            break;
        case State::Type::TwoRanges1:
            setSelectionTwoRanges1(selection);
            break;
        case State::Type::Finish1Range:
            setSelectionFinish1Range(selection);
            break;
        case State::Type::Finish2Ranges:
            setSelectionFinish2Ranges(selection);
            break;
        case State::Type::Invalid:
            selection.setGroup(0, CoinGroup::Guess);
            break;
    }
}

void ComputerMedium1::changeState(const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Balance:
            afterWeighBalance();
            break;
        case WeighResult::LeftHeavy:
            afterWeighLeftHeavy();
            break;
        case WeighResult::RightHeavy:
            afterWeighRightHeavy();
            break;
        default:
            throw Exception<ComputerMedium1>("Should be guessing.");
    }
}



//************************** Helper functions for pickToWeigh
const bool ComputerMedium1::readyToGuess() const {
    return (state.type == State::Type::Finish1Range ||
            state.type == State::Type::Finish2Ranges);
}

void ComputerMedium1::setSelectionOneRange(CoinSelection &selection) const {
    const size_t weighPileSize = splitSize(state.range1);
    const size_t rangeBegin = state.range1.begin();
    const size_t rangeEnd = state.range1.end();
    
    for (size_t i = rangeBegin; i < rangeBegin + weighPileSize; ++i) {
        selection.setGroup(i, CoinGroup::LeftWeigh);
    }
    
    for (size_t i = rangeEnd - weighPileSize; i < rangeEnd; ++i) {
        selection.setGroup(i, CoinGroup::RightWeigh);
    }
}

void ComputerMedium1::setSelectionTwoRanges0(CoinSelection &selection) const {
    const size_t weighPileSize = splitSize(state.range1);
    const size_t rangeBegin = state.range1.begin();
    const size_t rangeEnd = state.range1.end();
    
    for (size_t i = rangeBegin; i < rangeBegin + weighPileSize; ++i) {
        selection.setGroup(i, CoinGroup::LeftWeigh);
    }
    
    for (size_t i = rangeEnd - weighPileSize; i < rangeEnd; ++i) {
        selection.setGroup(i, CoinGroup::RightWeigh);
    }
}

void ComputerMedium1::setSelectionTwoRanges1(CoinSelection &selection) const {
    const size_t weighPileSize = splitSize(state.range2);
    const size_t rangeBegin = state.range2.begin();
    const size_t rangeEnd = state.range2.end();
    
    for (size_t i = rangeBegin; i < rangeBegin + weighPileSize; ++i) {
        selection.setGroup(i, CoinGroup::LeftWeigh);
    }
    
    for (size_t i = rangeEnd - weighPileSize; i < rangeEnd; ++i) {
        selection.setGroup(i, CoinGroup::RightWeigh);
    }
}

void ComputerMedium1::setSelectionFinish1Range(CoinSelection &selection) const {
    selection.setGroup(state.range1.begin(), CoinGroup::Guess);
    selection.setGroup(state.range1.begin() + 1, CoinGroup::Guess);
}

void ComputerMedium1::setSelectionFinish2Ranges(CoinSelection &selection) const {
    selection.setGroup(state.range1.begin(), CoinGroup::Guess);
    selection.setGroup(state.range2.begin(), CoinGroup::Guess);
}



//************************** Helper functions for afterWeigh
void ComputerMedium1::afterWeighLeftHeavy() {
    switch (state.type) {
        case State::Type::OneRange:
            splitCheckLeftHeavyTwoFakes();
            break;
        case State::Type::TwoRanges0:
            splitLeftHeavyOneFake(state.range1);
            checkRange1OneFake();
            break;
        case State::Type::TwoRanges1:
            splitLeftHeavyOneFake(state.range2);
            checkRange2OneFake();
            break;
        default:
            internalBug();
    }
}

void ComputerMedium1::afterWeighRightHeavy() {
    switch (state.type) {
        case State::Type::OneRange:
            splitCheckRightHeavyTwoFakes();
            break;
        case State::Type::TwoRanges0:
            splitRightHeavyOneFake(state.range1);
            checkRange1OneFake();
            break;
        case State::Type::TwoRanges1:
            splitRightHeavyOneFake(state.range2);
            checkRange2OneFake();
            break;
        default:
            internalBug();
    }
}

void ComputerMedium1::afterWeighBalance() {
    switch (state.type) {
        case State::Type::OneRange:
            splitCheckBalanceTwoFakes();
            break;
        case State::Type::TwoRanges0:
            splitBalanceOneFake(state.range1);
            checkRange1OneFake();
            break;
        case State::Type::TwoRanges1:
            splitBalanceOneFake(state.range2);
            checkRange2OneFake();
            break;
        default:
            internalBug();
    }
}



//************************** Helper functions for splitting with two fake coins
void ComputerMedium1::splitCheckLeftHeavyTwoFakes() {
    state.range1.setLowerBound(state.range1.begin() + splitSize(state.range1));
    switch (state.range1.size()) {
        case 0:
        case 1:
            internalBug();
        case 2:
            state.type = State::Type::Finish1Range;
            break;
        default:
            break;
    }
}

void ComputerMedium1::splitCheckRightHeavyTwoFakes() {
    state.range1.setUpperBound(state.range1.end() - splitSize(state.range1));
    switch (state.range1.size()) {
        case 0:
        case 1:
            internalBug();
        case 2:
            state.type = State::Type::Finish1Range;
            break;
        default:
            break;
    }
}

void ComputerMedium1::splitCheckBalanceTwoFakes() {
    state.range2.setBounds(state.range1.end() - splitSize(state.range1), state.range1.end());
    state.range1.setUpperBound(state.range1.begin() + splitSize(state.range1));
    switch (state.range1.size()) {
        case 0:
            internalBug();
        case 1:
            state.type = State::Type::Finish2Ranges;
            break;
        default:
            state.type = State::Type::TwoRanges0;
            break;
    }
}



//************************** Static functions for general splitting with one fake coin
void ComputerMedium1::splitLeftHeavyOneFake(Range &range) {
    range.setLowerBound(range.end() - splitSize(range));
}

void ComputerMedium1::splitRightHeavyOneFake(Range &range) {
    range.setUpperBound(range.begin() + splitSize(range));
}

void ComputerMedium1::splitBalanceOneFake(Range &range) {
    const size_t weighPileSize = splitSize(range);
    range.setBounds(range.begin() + weighPileSize, range.end() - weighPileSize);
}



//************************** Range checker for splitting with one fake coin
void ComputerMedium1::checkRange1OneFake() {
    switch (state.range1.size()) {
        case 0:
            internalBug();
        case 1:
            state.type = State::Type::TwoRanges1;
            if (state.range2.size() == 1) {
                internalBug();
            }
            break;
        default:
            break;
    }
}

void ComputerMedium1::checkRange2OneFake() {
    switch (state.range2.size()) {
        case 0:
            internalBug();
        case 1:
            state.type = State::Type::Finish2Ranges;
            break;
        default:
            break;
    }
}



//************************** Split size
const size_t ComputerMedium1::splitSize(const Range &range) {
    return range.size() / 2;
}



//************************** Bug handling
void ComputerMedium1::internalBug() throw (Exception<ComputerMedium1>) {
    throw Exception<ComputerMedium1>("Internal bug.");
}

template<> const std::string Exception<ComputerMedium1>::headerMessage() const {
    return "Computer Medium 1: ";
}
