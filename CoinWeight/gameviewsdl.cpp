//
//  gameviewsdl.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewsdl.hpp"

GameViewSDL::GameViewSDL() : coreGraphics() {
    timer = SDL_AddTimer(callbackDelay, <#SDL_TimerCallback callback#>, <#void *param#>)
}