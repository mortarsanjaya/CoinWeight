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
#include <chrono>
#include <thread>
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
    //view = std::make_unique<GameViewSDL>();
    if (view == nullptr) {
        cout << "Oops. Cannot open display." << endl;
        return 0;
    }
    
    sleep(1);
    model->updateView(view.get());
    while (true) {
        vector<Input> inputs = view->processInputs();
        for (Input &input : inputs) {
            controller.onReceivingInput(*model, input);
        }
        auto start = std::chrono::system_clock::now();
        model->updateView(view.get());
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << diff.count() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
