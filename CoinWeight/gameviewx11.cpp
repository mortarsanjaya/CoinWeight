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
    
    drawCoin(0, 0, 0);
}

//******************************************************************************

void GameViewX11::drawCoin(int x_pos, int y_pos, size_t coinIndex) {
    coreGraphics.drawCircle(x_pos, y_pos, coinRadius, X11Graphics::Black);
    coreGraphics.fillCircle(x_pos, y_pos, coinRadius, X11Graphics::Gold);
    // The index for drawing starts at 1, not 0, to avoid confusion
    coreGraphics.drawString(x_pos, y_pos, std::to_string(coinIndex + 1));
}
