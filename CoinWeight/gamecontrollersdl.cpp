//
//  gamecontrollersdl.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontrollersdl.hpp"

GameControllerSDL::GameControllerSDL() {
}

void GameControllerSDL::startEventLoop() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                //gameEngine->onKeyPress(event.key.keysym.sym);
                break;
            case SDL_QUIT:
                //gameEngine->quit();
                break;
        }
    }
}
