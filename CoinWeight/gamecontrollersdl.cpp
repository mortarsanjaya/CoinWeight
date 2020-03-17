//
//  gamecontrollersdl.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontrollersdl.hpp"

GameControllerSDL::GameControllerSDL(Game *game) {
    this->game = game;
}

void GameControllerSDL::eventLoop() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                game->onKeyPress(event.key.keysym.sym);
                break;
            case SDL_QUIT:
                game->quit();
                break;
        }
    }
}
