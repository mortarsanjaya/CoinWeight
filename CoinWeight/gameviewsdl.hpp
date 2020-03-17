//
//  gameviewsdl.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameviewsdl_hpp
#define gameviewsdl_hpp

#include "sdlgraphics.hpp"

class GameViewSDL {
    SDLGraphics coreGraphics;
    SDL_TimerID timer;
    bool done;
    
    static const int callbackDelay = 30;
    
public:
    GameViewSDL();
};

#endif /* gameviewsdl_hpp */
