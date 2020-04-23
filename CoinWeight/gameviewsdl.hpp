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
#include "gameview.hpp"

class GameViewSDL : public GameView {
    SDLGraphics coreGraphics;
    SDL_Window *mainWindow;
    SDL_Window *historyWindow;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Event event;
    
    void drawText(std::string text, int x, int y, int fontSize, bool selected = false);
    void drawInputBox(std::string infoText, std::string inputText, int x, int y, bool selected = false);
    void drawCoin(std::string coinNumber, int x, int y, bool selected = false);
    void drawRectangle(int x, int y, int width, int height, int red, int green, int blue);
    void drawButton(std::string text, int x, int y, bool selected = false);
    void drawScale(int tilt, int leftCoinsCount, int rightCoinsCount);
    
    static const int WIDTH = 800;
    static const int HEIGHT = 600;
    
public:
    GameViewSDL();
    
    virtual void receiveInput() override;
    virtual const Input lastInput() override;
    
    //virtual void drawMainScreen(const int screenHighlight) override;
    virtual void drawInstructionScreen() override;
    virtual void drawCreditScreen() override;
    //virtual void drawGameOptionScreen(const int screenHighlight, const size_t numOfCoins,
      //                                const std::string &gameLevel, const bool isHuman) override;
};

#endif /* gameviewsdl_hpp */
