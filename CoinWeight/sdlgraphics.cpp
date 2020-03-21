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

SDLGraphics::SDLGraphics(int width, int height) {
    // Initialize everything
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        throw SDLException("Unable to initialize SDL.");
    }

    // Create a Window
    window = SDL_CreateWindow("Coin Weighting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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
    renderer = SDL_GetRenderer(window);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        throw SDLException("Unable to create renderer.");
    }
    
    TTF_Init();
}
    
void SDLGraphics::drawText(std::string text, int x, int y, int fontSize, bool selected) {
    TTF_Font* Sans = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 24);
    if (Sans == nullptr) {
        throw SDLException("Unable to create sans.");
    }
    SDL_Color White = {255, 255, 255};

    surface = TTF_RenderText_Solid(Sans, "textextext", White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x;  //controls the rect's x coordinate
    Message_rect.y = y; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    
    SDL_RenderPresent(renderer);
}
    
void SDLGraphics::drawInputBox(std::string infoText, std::string inputText, int x, int y, bool selected) {
    
}

void SDLGraphics::drawCoin(std::string coinNumber, int x, int y, bool selected) {
    
}

void SDLGraphics::drawRectangle(int x, int y, int width, int height, int red, int green, int blue) {
    //SDL_Color color = {red, green, blue};
}

void SDLGraphics::drawButton(std::string text, int x, int y, bool selected) {
    
}

void SDLGraphics::drawScale(int tilt, int leftCoinsCount, int rightCoinsCount) {
    
}

void SDLGraphics::receiveInput() {
    SDL_PollEvent(&event);
}

const Input SDLGraphics::lastInput() const {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP: return Input(Input::Arrow::Up);
                case SDLK_LEFT: return Input(Input::Arrow::Left);
                case SDLK_RIGHT: return Input(Input::Arrow::Right);
                case SDLK_DOWN: return Input(Input::Arrow::Down);
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER: return Input('\n');
                case SDLK_0:
                case SDLK_KP_0: return Input('0');
                case SDLK_1:
                case SDLK_KP_1: return Input('1');
                case SDLK_2:
                case SDLK_KP_2: return Input('2');
                case SDLK_3:
                case SDLK_KP_3: return Input('3');
                case SDLK_4:
                case SDLK_KP_4: return Input('4');
                case SDLK_5:
                case SDLK_KP_5: return Input('5');
                case SDLK_6:
                case SDLK_KP_6: return Input('6');
                case SDLK_7:
                case SDLK_KP_7: return Input('7');
                case SDLK_8:
                case SDLK_KP_8: return Input('8');
                case SDLK_9:
                case SDLK_KP_9: return Input('9');
                default: break;
            }
            break;
        case SDL_QUIT:
            SDL_Quit();
            return Input();
            break;
        default:
            return Input();
    }
    return Input();
}
