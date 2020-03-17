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
    void showText(std::string text, int x, int y, bool selected = false);
    void showInput()
};

#endif /* sdlgraphics_hpp */
