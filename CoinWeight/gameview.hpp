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
    GameViewX11(int numOfCoins);
    void play();
    void gotoInstructions();
};

#endif
