//
//  gamecontrollersdl.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecontrollersdl_hpp
#define gamecontrollersdl_hpp

#include "SDL2/SDL.h"
#include "gameengine.hpp"

class GameControllerSDL {
    SDL_Event event;
    GameEngine *gameEngine;
    
public:
    GameControllerSDL(GameEngine *gameEngine);
    void startEventLoop();
};

#endif /* gamecontrollersdl_hpp */
