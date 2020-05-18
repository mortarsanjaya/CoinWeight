//
//  gamesettings.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesettings.hpp"

//***************************************************** Constructor
GameSettings::GameSettings() : gameSize(defaultNumOfCoins),
    level(defaultLevel), isHuman(defaultIsHuman) {}
    
    
    
//***************************************************** Field accessors
const size_t GameSettings::numOfCoins() const {
    return gameSize;
}

const GameLevel GameSettings::gameLevel() const {
    return level;
}

const bool GameSettings::isHumanMode() const {
    return isHuman;
}



//***************************************************** Modifier functions
void GameSettings::increaseNumOfCoins() {
    if (gameSize < numOfCoinsUpperBound) {
        ++gameSize;
    }
}

void GameSettings::decreaseNumOfCoins() {
    if (gameSize > numOfCoinsLowerBound) {
        --gameSize;
    }
}

void GameSettings::increaseLevel() {
    switch (level) {
        case GameLevel::Easy:
            level = GameLevel::Medium;
            break;
        case GameLevel::Medium:
            level = GameLevel::Hard;
            break;
        case GameLevel::Hard:
            level = GameLevel::Hard;
            break;
    }
}

void GameSettings::decreaseLevel() {
    switch (level) {
        case GameLevel::Easy:
            level = GameLevel::Easy;
            break;
        case GameLevel::Medium:
            level = GameLevel::Easy;
            break;
        case GameLevel::Hard:
            level = GameLevel::Medium;
            break;
    }
}

void GameSettings::switchMode() {
    isHuman = !isHuman;
}
