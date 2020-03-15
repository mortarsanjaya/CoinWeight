//
//  sdlgraphics.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 14/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef sdlgraphics_hpp
#define sdlgraphics_hpp

#include "SDL2/SDL.h"

class SDLGraphics {
    SDL_Window *window;
    SDL_Renderer *renderer;
    
public:
    SDLGraphics();
    void showTitleScreen();
    
};

#endif /* sdlgraphics_hpp */
