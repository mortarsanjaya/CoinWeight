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
    sleep(1);
    gameModel->updateView(*gameView);
    sleep(1);
    while (true) {
        std::string s;
        cin >> s;
        if (cin.fail()) break;
        Input inp(s[0]);
        if (s[0] == 'n') {
            inp = Input('\n');
        } else if (s[0] == 'u') {
            inp = Input(Input::Arrow::Up);
        } else if (s[0] == 'j') {
            inp = Input(Input::Arrow::Down);
        } else if (s[0] == 'h') {
            inp = Input(Input::Arrow::Left);
        } else if (s[0] == 'k') {
            inp = Input(Input::Arrow::Right);
        }
        gameModel->processInput(inp);
        gameModel->updateView(*gameView);
    }
}

/*
    README
    Game Model components pretty much done
    The Game Model itself is far from done, I'd say
    Game View is also quite far from done
    However, looking at the design (and the fact that we're not
        time-pressured, this is not the biggest issue)
*/
