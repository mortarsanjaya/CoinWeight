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
#include "SDL2_ttf/SDL_ttf.h"

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
    
    surface = SDL_GetWindowSurface(window);
    if (surface == nullptr) {
        SDL_Log("Unable to get window surface: %s", SDL_GetError());
        throw SDLException("Unable to get surface.");
    }
    
    // Create a Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        throw SDLException("Unable to create renderer.");
    }
}
    
void SDLGraphics::drawText(std::string text, int x, int y, bool selected) {
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x;  //controls the rect's x coordinate
    Message_rect.y = y; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    
    SDL_RenderPresent(renderer);
}
    
void SDLGraphics::drawInputBox(std::string text, int x, int y, bool selected) {
    
}
void SDLGraphics::drawCoin(std::string coinNumber, int x, int y, bool selected) {
    
}
void SDLGraphics::drawRectangle(int x, int y, int width, int height, int red, int green, int blue) {
    
}

void SDLGraphics::drawButton(std::string text, int x, int y, bool selected) {
    
}

void SDLGraphics::drawScale(int tilt, int leftCoinsCount, int rightCoinsCount) {
    
}
