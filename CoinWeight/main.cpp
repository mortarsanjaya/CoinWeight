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
#include "controller.hpp"
#include "viewx11.hpp"

#include <chrono>
#include <thread>

using namespace std;

int main() {
    // computerTest(50, GameLevel::Easy);
    // computerTest(75, GameLevel::Medium);

    auto view = std::make_unique<Controller>(std::make_unique<ViewX11>());
    while (true) {
        view->updateDisplay();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        view->processInput();
    }
}
