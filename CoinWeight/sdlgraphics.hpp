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
#include <string>

class SDLGraphics {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    
public:
    SDLGraphics();
    void drawText(std::string text, int x, int y, bool selected = false);
    void drawInputBox(std::string text, int x, int y, bool selected = false);
    void drawCoin(std::string coinNumber, int x, int y, bool selected = false);
    void drawRectangle(int x, int y, int width, int height, int red, int green, int blue);
    void drawButton(std::string text, int x, int y, bool selected = false);
    void drawScale(int tilt, int leftCoinsCount, int rightCoinsCount);
    // tilt: -1 for left heavy, 0 for neutral, 1 for right heavy (maybe enum class is better)
};

#endif /* sdlgraphics_hpp */
