//
//  computereasy1.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-29.
//  Copyright © 2020 -. All rights reserved.
//

#include "computereasy1.hpp"
#include "exception.hpp"

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
            return firstMoveAfterWeigh(weighResult);
        case State::Type::SecondMove:
            return secondMoveAfterWeigh(weighResult);
        case State::Type::Coin0IsFake:
            return coin0IsFakeAfterWeigh(weighResult);
        case State::Type::Coin0IsReal0:
            return coin0IsReal0AfterWeigh(weighResult);
        case State::Type::Coin0IsReal1:
            return coin0IsReal1AfterWeigh(weighResult);
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
void ComputerEasy1::firstMoveAfterWeigh(const WeighResult weighResult) {
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

void ComputerEasy1::secondMoveAfterWeigh(const WeighResult weighResult) {
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

void ComputerEasy1::coin0IsFakeAfterWeigh(const WeighResult weighResult) {
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

void ComputerEasy1::coin0IsReal0AfterWeigh(const WeighResult weighResult) {
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

void ComputerEasy1::coin0IsReal1AfterWeigh(const WeighResult weighResult) {
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
