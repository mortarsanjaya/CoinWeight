//
//  computereasy1.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "computereasy1.hpp"
#include "exception.hpp"

/*
Small documentation for the computer strategy:
The computer compares Coin 0 against all other single coins each
If Coin 0 is fake, the first two moves finds that it is indeed fake
In fact, in this case, if the second move is necessary, Coin 0 and 1 are fake
In both cases, after determining if Coin 0 is genuine, all other coins
    can be determined by comparing against coin 0
 */

//************************** Constructor
ComputerEasy1::ComputerEasy1(const size_t numOfCoins) :
Computer{numOfCoins}, state{State::Type::FirstMove}, testIndex{1} {}



//************************** Overriding functions
void ComputerEasy1::beforeWeigh() {}
void ComputerEasy1::pickToWeigh(CoinStates &coinStates) const {
    if (testIndex == nCoins) {
        throw Exception<ComputerEasy1>("Should be guessing.");
    }
    coinStates.moveToLeftWeighGroup(0);
    coinStates.moveToRightWeighGroup(testIndex);
}

void ComputerEasy1::afterWeigh(const WeighResult weighResult) {
    switch (state.type) {
        case State::Type::FirstMove:
            return afterWeighFirstMove(weighResult);
        case State::Type::SecondMove:
            return afterWeighSecondMove(weighResult);
        case State::Type::Coin0IsFake:
            return afterWeighCoin0IsFake(weighResult);
        case State::Type::Coin0IsReal0:
            return afterWeighCoin0IsReal0(weighResult);
        case State::Type::Coin0IsReal1:
            return afterWeighCoin0IsReal1(weighResult);
        case State::Type::Finish:
            throw Exception<ComputerEasy1>("Should be guessing.");
    }
}

void ComputerEasy1::pickToGuess(CoinStates &coinStates) const {
    if (!readyToGuess()) {
        throw Exception<ComputerEasy1>("Should be weighing.");
    }
    
    coinStates.moveToGuessGroup(state.fakeCoin1);
    coinStates.moveToGuessGroup(state.fakeCoin2);
}

const bool ComputerEasy1::readyToGuess() const {
    return (state.type == State::Type::Finish);
}



//************************** Private member methods
void ComputerEasy1::afterWeighFirstMove(const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Balance:
            state.type = State::Type::SecondMove;
            break;
        case WeighResult::LeftHeavy:
            state.type = State::Type::Coin0IsReal1;
            state.fakeCoin1 = testIndex;
            break;
        case WeighResult::RightHeavy:
            state.type = State::Type::Coin0IsFake;
            state.fakeCoin1 = 0;
            break;
        default:
            throw Exception<ComputerEasy1>("Invalid weighing result.");
    }
    ++testIndex;
}

void ComputerEasy1::afterWeighSecondMove(const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Balance:
            state.type = State::Type::Coin0IsReal0;
            break;
        case WeighResult::LeftHeavy:
            state.type = State::Type::Coin0IsReal1;
            state.fakeCoin1 = testIndex;
            break;
        case WeighResult::RightHeavy:
            state.type = State::Type::Finish;
            state.fakeCoin1 = 0;
            state.fakeCoin2 = testIndex;
            break;
        default:
            throw Exception<ComputerEasy1>("Invalid weighing result.");
    }
    ++testIndex;
}

void ComputerEasy1::afterWeighCoin0IsFake(const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Balance:
            state.type = State::Type::Finish;
            state.fakeCoin2 = testIndex;
            break;
        case WeighResult::RightHeavy:
            break;
        default:
            throw Exception<ComputerEasy1>("Invalid weighing result.");
    }
    ++testIndex;
}

void ComputerEasy1::afterWeighCoin0IsReal0(const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Balance:
            break;
        case WeighResult::LeftHeavy:
            state.type = State::Type::Coin0IsReal1;
            state.fakeCoin1 = testIndex;
            break;
        default:
            throw Exception<ComputerEasy1>("Invalid weighing result.");
    }
    ++testIndex;
}

void ComputerEasy1::afterWeighCoin0IsReal1(const WeighResult weighResult) {
    switch (weighResult) {
        case WeighResult::Balance:
            break;
        case WeighResult::LeftHeavy:
            state.type = State::Type::Finish;
            state.fakeCoin2 = testIndex;
            break;
        default:
            throw Exception<ComputerEasy1>("Invalid weighing result.");
    }
    ++testIndex;
}