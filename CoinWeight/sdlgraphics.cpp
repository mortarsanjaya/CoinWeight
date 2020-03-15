//
//  sdlgraphics.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 14/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include "sdlgraphics.hpp"

SDLGraphics::SDLGraphics() {
    // Initialize everything
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    // Create a Window
    window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        exit(1);
    }
    // Declaring the surface.
    SDL_Surface *s;

    // Creating the surface.
    s = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);

    // Filling the surface with red color.
    SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));

    // Create a Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        exit(1);
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, s);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    SDL_RenderClear(renderer); // Fill render with color
    SDL_RenderCopy(renderer, texture, NULL, NULL); // Copy the texture into render
    SDL_RenderPresent(renderer); // Show render on window
    
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }
}

void SDLGraphics::showTitleScreen() {
    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);
    SDL_Surface *titleScreen = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, titleScreen);
    SDL_FreeSurface(titleScreen);
    if (texture == nullptr){
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        exit(1);
    }

    /* Draw the render on window */
    SDL_RenderClear(renderer); // Fill render with color
    SDL_RenderCopy(renderer, texture, NULL, NULL); // Copy the texture into render
    SDL_RenderPresent(renderer); // Show render on window
    SDL_Delay(5000);
    
    /* Free all objects*/
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit program */
    SDL_Quit();
}
