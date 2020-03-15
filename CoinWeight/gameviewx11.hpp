//
//  gameviewx11.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameviewx11_hpp
#define gameviewx11_hpp

#include <iostream>
#include <memory>
#include "gameview.hpp"
#include "x11graphics.hpp"

class GameViewX11 {
	X11Graphics coreGraphics;

public:
    GameViewX11(int numOfCoins);
};

#endif
