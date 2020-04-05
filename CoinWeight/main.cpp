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
#include "gamecontroller.hpp"
#include "input.hpp"

int main() {
    auto gameModel = std::make_unique<GameModel>();
    auto gameView = std::make_unique<GameViewX11>();
    auto gameController = std::make_unique<GameController>(gameModel.release(), gameView.release());
    gameController->updateView();
    sleep(1);
    while (true) {
        gameController->receiveInput();
        gameController->updateView();
    }
}
