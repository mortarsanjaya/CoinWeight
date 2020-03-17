//
//  sdlgraphics.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 14/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <string>
#include "sdlgraphics.hpp"
#include "sdlexception.hpp"

SDLGraphics::SDLGraphics() {
    // Initialize everything
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        throw SDLException("Unable to initialize SDL.");
    }

    // Create a Window
    window = SDL_CreateWindow("Coin Weighting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        throw SDLException("Unable to create window.");
    }
    
    // Create a Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        throw SDLException("Unable to create renderer.");
    }
    /*
    SDL_Surface *s;
    
    s = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);

    // Filling the surface with red color.
    SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));*/
}
