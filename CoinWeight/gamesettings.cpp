//
//  gamesettings.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamesettings.hpp"

//***************************************************** Constructor
GameSettings::GameSettings(int numOfCoins, GameLevel level, bool isHuman) :
    numOfCoins(numOfCoins), level(level), isHuman(isHuman) {}
    
    
    
//***************************************************** Field accessors
const int GameSettings::gameSize() const {
    return numOfCoins;
}

const GameLevel GameSettings::gameLevel() const {
    return level;
}

const bool GameSettings::isHumanMode() const {
    return isHuman;
}



//***************************************************** Modifier functions
void GameSettings::increaseGameSize() {
    if (numOfCoins < numOfCoinsUpperBound) {
        ++numOfCoins;
    }
}

void GameSettings::decreaseGameSize() {
    if (numOfCoins > numOfCoinsLowerBound) {
        --numOfCoins;
    }
}

void GameSettings::increaseDifficulty() {
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

void GameSettings::decreaseDifficulty() {
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



//***************************************************** Number of coins bound
const int GameSettings::numOfCoinsLowerBound = 2;
const int GameSettings::numOfCoinsUpperBound = 100;
