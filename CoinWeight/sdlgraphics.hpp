//
//  sdlgraphics.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 14/03/20.
//  Copyright © 2020 -. All rights reserved.
//

// to transfer over to gameviewsdl

#ifndef sdlgraphics_hpp
#define sdlgraphics_hpp

#include "SDL2/SDL.h"
#include "input.hpp"
#include <string>

class SDLGraphics {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Event event;
    
public:
    SDLGraphics(int width, int height);
    void drawText(std::string text, int x, int y, int fontSize, bool selected = false);
    void drawInputBox(std::string infoText, std::string inputText, int x, int y, bool selected = false);
    void drawCoin(std::string coinNumber, int x, int y, bool selected = false);
    void drawRectangle(int x, int y, int width, int height, int red, int green, int blue);
    void drawButton(std::string text, int x, int y, bool selected = false);
    void drawScale(int tilt, int leftCoinsCount, int rightCoinsCount);
    // tilt: -1 for left heavy, 0 for neutral, 1 for right heavy (maybe enum class is better)
    
    void receiveInput();
    const Input lastInput() const;
};

#endif /* sdlgraphics_hpp */
