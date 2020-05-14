//
//  computermedium1.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "computermedium1.hpp"
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

//************************** Constructor (+ State)
ComputerMedium1::ComputerMedium1(const size_t numOfCoins) :
Computer(numOfCoins), state(numOfCoins) {}

ComputerMedium1::State::State(const size_t numOfCoins) :
type{Type::OneRange}, range1{0, numOfCoins} {}



//************************** Overriding functions
void ComputerMedium1::beforeWeigh() {}
void ComputerMedium1::pickToWeigh(CoinSelection &coinStates) const {
    switch (state.type) {
        case State::Type::OneRange:
            pickToWeighOneRange(coinStates);
            break;
        case State::Type::TwoRanges0:
            pickToWeighTwoRanges0(coinStates);
            break;
        case State::Type::TwoRanges1:
            pickToWeighTwoRanges1(coinStates);
            break;
        default:
            throw Exception<ComputerMedium1>("Should be guessing.");
    }
}

void ComputerMedium1::afterWeigh(const WeighResult weighResult) {
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


void ComputerMedium1::pickToGuess(CoinSelection &coinStates) const {
    if (!readyToGuess()) {
        throw Exception<ComputerMedium1>("Should be weighing.");
    }
    
    coinStates.moveToGuessGroup(state.range1.begin);
    coinStates.moveToGuessGroup(state.range2.begin);
}

const bool ComputerMedium1::readyToGuess() const {
    return (state.type == State::Type::Finish);
}



//************************** Helper functions for pickToWeigh
void ComputerMedium1::pickToWeighOneRange(CoinSelection &coinStates) const {
    pickToWeighPileEndSplit(coinStates, state.range1, weighPileSizeTwoFakes(state.range1));
}

void ComputerMedium1::pickToWeighTwoRanges0(CoinSelection &coinStates) const {
    pickToWeighPileEndSplit(coinStates, state.range1, weighPileSizeOneFake(state.range1));
}

void ComputerMedium1::pickToWeighTwoRanges1(CoinSelection &coinStates) const {
    pickToWeighPileEndSplit(coinStates, state.range2, weighPileSizeOneFake(state.range2));
}

void ComputerMedium1::pickToWeighPileEndSplit(CoinSelection &coinStates,
const State::Range &range, const size_t weighPileSize) {
    for (size_t i = range.begin; i < range.begin + weighPileSize; ++i) {
        coinStates.moveToLeftWeighGroup(i);
    }
    
    for (size_t i = range.end - weighPileSize; i < range.end; ++i) {
        coinStates.moveToRightWeighGroup(i);
    }
}

const size_t ComputerMedium1::weighPileSizeTwoFakes(const State::Range &range) {
    return range.size() / 2;
}

const size_t ComputerMedium1::weighPileSizeOneFake(const State::Range &range) {
    return range.size() / 2;
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
            throw Exception<ComputerMedium1>("Internal bug.");
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
            throw Exception<ComputerMedium1>("Internal bug.");
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
            throw Exception<ComputerMedium1>("Internal bug.");
    }
}



//************************** Helper functions for splitting with two fake coins
void ComputerMedium1::splitCheckLeftHeavyTwoFakes() {
    state.range1.begin += weighPileSizeTwoFakes(state.range1);
    switch (state.range1.size()) {
        case 0:
        case 1:
            throw Exception<ComputerMedium1>("Internal bug.");
        case 2:
            state.type = State::Type::Finish;
            state.range2.begin = state.range1.begin + 1;
            state.range2.end = state.range2.begin + 1;
            break;
        default:
            break;
    }
}

void ComputerMedium1::splitCheckRightHeavyTwoFakes() {
    state.range1.end -= weighPileSizeTwoFakes(state.range1);
    switch (state.range1.size()) {
        case 0:
        case 1:
            throw Exception<ComputerMedium1>("Internal bug.");
        case 2:
            state.type = State::Type::Finish;
            state.range2.begin = state.range1.begin + 1;
            state.range2.end = state.range2.begin + 1;
            break;
        default:
            break;
    }
}

void ComputerMedium1::splitCheckBalanceTwoFakes() {
    state.range2.end = state.range1.end;
    state.range2.begin = state.range1.end - weighPileSizeTwoFakes(state.range1);
    state.range1.end = state.range1.begin + weighPileSizeTwoFakes(state.range1);
    switch (state.range1.size()) {
        case 0:
            throw Exception<ComputerMedium1>("Internal bug.");
        case 1:
            state.type = State::Type::Finish;
            break;
        default:
            state.type = State::Type::TwoRanges0;
            break;
    }
}



//************************** Static functions for general splitting with one fake coin
void ComputerMedium1::splitLeftHeavyOneFake(State::Range &range) {
    range.begin = range.end - weighPileSizeOneFake(range);
}

void ComputerMedium1::splitRightHeavyOneFake(State::Range &range) {
    range.end = range.begin + weighPileSizeOneFake(range);
}



void ComputerMedium1::splitBalanceOneFake(State::Range &range) {
    const size_t weighPileSize = weighPileSizeOneFake(range);
    range.begin += weighPileSize;
    range.end -= weighPileSize;
    if (range.begin >= range.end) {
        throw Exception<ComputerMedium1>("Internal bug.");
    } // Should be dead but whatever
}



//************************** Range checker for splitting with one fake coin
void ComputerMedium1::checkRange1OneFake() {
    switch (state.range1.size()) {
        case 0:
            throw Exception<ComputerMedium1>("Internal bug.");
        case 1:
            state.type = State::Type::TwoRanges1;
            if (state.range2.size() == 1) {
                throw Exception<ComputerMedium1>("Internal bug.");
            }
            break;
        default:
            break;
    }
}

void ComputerMedium1::checkRange2OneFake() {
    switch (state.range2.size()) {
        case 0:
            throw Exception<ComputerMedium1>("Internal bug.");
        case 1:
            state.type = State::Type::Finish;
            break;
        default:
            break;
    }
}



//************************** Range size checker
const size_t ComputerMedium1::State::Range::size() const {
    return end - begin;
}
