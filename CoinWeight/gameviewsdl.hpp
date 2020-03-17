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
    
    static const int callbackDelay = 30;
    
public:
    GameViewSDL();
    
    virtual void drawMainScreen() override;
    virtual void drawPlayScreen1() override;
    virtual void drawInstructionScreen() override;
    virtual void drawPlayScreen2(int numOfCoins) override;
};

#endif /* gameviewsdl_hpp */
