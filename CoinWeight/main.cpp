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
#include "gameviewx11.hpp"
#include "gameviewsdl.hpp"
#include "gamecontroller.hpp"
#include "input.hpp"

int main() {
    auto gameController = std::make_unique<GameController>(new GameModel, new GameViewX11);
    gameController->updateView();
    //sleep(1);
    while (true) {
        gameController->receiveInput();
        gameController->updateView();
    }
}
