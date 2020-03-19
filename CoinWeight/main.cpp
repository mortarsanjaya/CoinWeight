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

using namespace std;

int main() {
    unique_ptr<GameViewX11> gameView = make_unique<GameViewX11>();
    sleep(2);
    std::vector<int> coinStates(39, 0);
    coinStates[12] = 1;
    coinStates[20] = 2;
    std::vector<std::pair<Weighing, int>> gameHistory;
    gameView->drawGamePlayScreen(coinStates, gameHistory);
    int x;
    cin >> x;
}
