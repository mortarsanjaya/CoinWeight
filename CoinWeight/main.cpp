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

using namespace std;

int main() {
    std::unique_ptr<GameModel> model;
    std::unique_ptr<GameView> view;
    GameController controller;
    
    model = std::make_unique<GameModel>();
    if (model == nullptr) {
        cout << "Oops. Cannot initialize model." << endl;
        return 0;
    }
    
    view = std::make_unique<GameViewX11>();
    if (view == nullptr) {
        cout << "Oops. Cannot open display." << endl;
        return 0;
    }
    
    sleep(1);
    model->updateView(view.get());
    while (true) {
        view->receiveInput();
        controller.onReceivingInput(*model, view->lastInput());
        model->updateView(view.get());
    }
}
