//
//  gameview.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameview_hpp
#define gameview_hpp

#include <iostream>

class GameView {
public:
    GameView() = default;
    virtual void drawMainScreen() = 0;
    virtual void drawPlayScreen1() = 0;
    virtual void drawInstructionScreen() = 0;
    virtual void drawPlayScreen2(int numOfCoins) = 0;
};

#endif
