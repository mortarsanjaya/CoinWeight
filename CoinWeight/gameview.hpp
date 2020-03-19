//
//  gameview.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameview_hpp
#define gameview_hpp

class GameView {
public:
    GameView() = default;
    virtual void drawMainScreen() = 0;
    virtual void drawInstructionScreen() = 0;
    virtual void drawCreditScreen() = 0;
    virtual void drawOptionSelectScreen() = 0;
    virtual void drawGameScreen(int numOfCoins) = 0;
    virtual void drawEndScreen() = 0;
};

#endif
