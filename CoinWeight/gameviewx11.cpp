//
//  gameviewx11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewx11.hpp"

GameViewX11::GameViewX11(int numOfCoins) : coreGraphics{"CoinWeight"} {
    coreGraphics.drawString(200, 200, "Coin Weighting");
    coreGraphics.drawString(200, 300, "Play");
    coreGraphics.drawString(200, 400, "Instructions");
}
