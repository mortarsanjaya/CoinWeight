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
#include "gameview.hpp"
#include "x11graphics.hpp"
#include <string>

class GameViewX11 : GameView {
public:
	X11Graphics coreGraphics;
 
 private:
    void drawCoin(int x_pos, int y_pos, size_t coinIndex);
    static const int coinRadius = 30;

public:
    GameViewX11();
    void drawMainScreen(int screenHighlight) override;
    void drawInstructionScreen() override;
    void drawCreditScreen() override;
    void drawGameOptionScreen(int screenHighlight, int numOfCoins,
            std::string gameLevel, bool isHuman) override;
    void drawGamePlayScreen(int numOfCoins, std::vector<int> coinStates,
            std::vector<std::pair<Weighing, int>> gameHistory) override;
    void drawGameOverScreen() override;
    
    char readKeyboardInput();
};

#endif
