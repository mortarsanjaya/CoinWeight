//
//  main.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>
#include "gamemodel.hpp"
#include "human.hpp"
#include "computerhard.hpp"
#include "x11graphics.hpp"
#include "sdlgraphics.hpp"
#include "gamecontrollersdl.hpp"

using namespace std;

int main() {
    //std::unique_ptr<GameViewSDL> gameView = std::make_unique<GameViewSDL>();
    //GameModel gameModel(std::move(gameView));
    //GameControllerSDL gameController(&gameEngine);
    //gameController.startEventLoop();
    SDLGraphics graphics;
    
    graphics.drawText("mytext", 50, 50);
    SDL_Delay(5000);
	return 0;
}
