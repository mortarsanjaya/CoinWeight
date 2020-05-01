//
//  player.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#include "player.hpp"
#include "computerfactory.hpp"
#include "exception.hpp"

//************************** Constructor
Player::Player(size_t numOfCoins) : coinStates(numOfCoins), history(), computer() {}
Player::Player(const size_t numOfCoins, const GameLevel gameLevel) :
    coinStates(numOfCoins), history(), computer()
{
    const auto &factory = ComputerFactory::createFactory(gameLevel);
    computer = factory->createComputer(numOfCoins);
    computerSetup();
}



//************************** Field accessors
const CoinStates &Player::currStates() const {
    return coinStates;
}

const History &Player::currHistory() const {
    return history;
}

const bool Player::isHuman() const {
    return !computer;
}

const bool Player::readyToGuess() const {
    return computer->readyToGuess();
}



//************************** Coin states manipulation
void Player::deselectCoin(const size_t coinIndex) {
    coinStates.deselect(coinIndex);
}

void Player::selectCoinToLeftGroup(const size_t coinIndex) {
    coinStates.moveToLeftWeighGroup(coinIndex);
}

void Player::selectCoinToRightGroup(const size_t coinIndex) {
    coinStates.moveToRightWeighGroup(coinIndex);
}

void Player::selectCoinToGuess(const size_t coinIndex) {
    coinStates.moveToGuessGroup(coinIndex);
}



//************************** Other public methods
void Player::receiveWeighResult(const WeighResult weighResult) {
    addWeighResult(weighResult);
    resetStates();
    if (computer) {
        computerSetup();
    }
}

void Player::historyIncrementIndex() {
    history.incrementIndex();
}

void Player::historyDecrementIndex() {
    history.decrementIndex();
}



//************************** Private methods
void Player::addWeighResult(const WeighResult weighResult) {
    history.addRecord(coinStates, weighResult);
    if (computer) {
        computer->afterWeigh(weighResult);
    }
}

void Player::resetStates() {
    coinStates.resetStates();
}

void Player::computerSetup() {
    if (!computer) {
        throw Exception<Player>("computerSetup: Not a computer.");
    }
    
    if (computer->readyToGuess()) {
        computer->pickToGuess(coinStates);
    } else {
        computer->beforeWeigh();
        computer->pickToWeigh(coinStates);
    }
}



//************************** Player exception
template<> const std::string exceptionHeaderMessage<Player>() {
    return "Player: ";
}
