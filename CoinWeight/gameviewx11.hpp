//
//  gameviewx11.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameviewx11_hpp
#define gameviewx11_hpp

#include <memory>
#include "game.hpp"
#include "x11graphics.hpp"
#include <string>

class GameViewX11 {
	X11Graphics coreGraphics;
    void drawCoin(int x_pos, int y_pos, size_t coinIndex);
    static const int coinRadius = 30;

public:
    GameViewX11();
    void drawMainPage();
    void play();
    void gotoInstructions();
    
    
};

#endif
