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
#include "input.hpp"

using namespace std;

int main() {
    std::unique_ptr<GameViewSDL> gameView = std::make_unique<GameViewSDL>();
    //GameModel gameModel(std::move(gameView));
    //GameControllerSDL gameController(&gameEngine);
    //gameController.startEventLoop();
    while (true) {
        gameView->receiveInput();
        gameView->lastInput();
        gameView->drawMainScreen(1);
    }
	return 0;
}
