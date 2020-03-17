//
//  gameengine.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 17/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameengine.hpp"

GameEngine::GameEngine(std::unique_ptr<GameViewSDL> gameView) : gameView(std::move(gameView)) {}
