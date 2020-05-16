//
//  main.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinset.hpp"
/*
#include "computer.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include "gamemodel.hpp"
#include "gameui_x11.hpp"
#include "gameview.hpp"
#include "gamecontroller.hpp"
#include "input.hpp"
*/
#include "computertest.hpp"
#include "gameview.hpp"
#include "gameui_x11.hpp"

#include <chrono>

/*
void play() {
    GameController controller;
    
    do {
    
        std::shared_ptr<GameModel> model;
        std::unique_ptr<GameView> view;
        
        model = std::make_shared<GameModel>();
        if (!model) {
            std::cout << "Oops. Cannot initialize model." << std::endl;
            return;
        } else {
            controller.registerModel(model);
        }
    
        view = std::make_unique<GameView>(std::make_unique<GameUI_X11>());
        if (!view) {
            std::cout << "Oops. Cannot open display." << std::endl;
            return;
        }
    
        controller.registerView(view);
    } while (false);
    
    sleep(1);
    controller.updateView();
    while (true) {
        controller.receiveInput();
        controller.onReceivingInput(controller.lastInput());
        controller.updateView();
    }
}
*/

#include <thread>

using namespace std;

int main() {
    computerTest(50, GameLevel::Easy);
    computerTest(75, GameLevel::Medium);
    
    auto view = std::make_unique<GameView>(std::make_unique<GameUI_X11>());
    while (true) {
        view->updateDisplay();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        
        
        view->processInput();
    }
}
