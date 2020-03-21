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
#include "input.hpp"

using namespace std;

int main() {
    std::unique_ptr<GameModel> gameModel;
    std::unique_ptr<GameViewX11> gameView;
    gameModel = make_unique<GameModel>();
    gameView = make_unique<GameViewX11>();
    gameModel->updateView(*gameView);
    while (true) {
        gameView->receiveInput();
        gameModel->processInput(gameView->lastInput());
        gameModel->updateView(*gameView);
    }
}
